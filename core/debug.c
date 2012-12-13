/*************************************************************************
@copyright Copyright (c) 2011 David Bunker

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*************************************************************************/

// this file is for debugging

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tbl.h"
#include "structs.h"
#include "arch.h"
#include "debug.h"
#include "var.h"
#include "../utils/linkedlist.h"
#include "../utils/gendebug.h"

/***************** Printing Debug Info *************/

int printVar(void *data){

	printVarData(stdout,(varData*)data);
	printf("\n");
	return 0;
}

void printDebugClause(FILE *file,linkedList clause){

	int c;
	int clauseLen = sizeLinked(clause);
	clauseVarData **varArray = toArrayLinked(clause);
	
	int start = 1;
	for(c=0;c<clauseLen;c++){	

		clauseVarData *cvd = varArray[c];
		assert(cvd,"Empty Clause Var");
		assert(cvd->data,"Empty Clause Var Data");

		if(!start)
			fprintf(file," OR ");
		start = 0;

		if(cvd->negate)
			fprintf(file,"NOT ");
		
		printVarData(file,cvd->data);
	}
	fprintf(file,"\n");
}

void printDebugClauses(char *fileName,indexList *varList,linkedList clauseList){

	FILE *file = fopen(fileName,"w");

	int i,c;
	int numVar = sizeVarList(varList);
	int numClause = sizeLinked(clauseList);
	fprintf(file,"p cnf %i %i\n",numVar,numClause);
	
	int listLen = sizeLinked(clauseList);
	linkedList **clauseArray = toArrayLinked(clauseList);
	
	for(i=0;i<listLen;i++){
		
		linkedList clause = clauseArray[i];
		int clauseLen = sizeLinked(clause);
		clauseVarData **varArray = toArrayLinked(clause);
		
		int start = 1;
		for(c=0;c<clauseLen;c++){	

			clauseVarData *cvd = varArray[c];
			assert(cvd,"Empty Clause Var");
			assert(cvd->data,"Empty Clause Var Data");

			if(!start)
				fprintf(file," OR ");
			start = 0;

			if(cvd->negate)
				fprintf(file,"NOT ");
			
			printVarData(file,cvd->data);
		}
		fprintf(file,"\n");
	}
	
	fclose(file);
}

/***************** Compiler Debugger *************/

// search for symbol list
int symNameSearch(void *param,void *data){
	
	int *p = param;
	symListInfo *dSym = data;
	
	if(*p == dSym->nameId) 
		return 0;
	return -1;
}

// check both name and obj match (for trans,req,desobj)
int fullSearch(void *param,void *data){

	nameData *pName = param;
	nameData *dName = data;

	if(pName->nameId == dName->nameId && pName->objId == dName->objId) 
		return 0;
	return -1;
}

// search for cell
int cellSearch(void *param,void *data){

	int *p = param;
	cellData *dCell = data;

	if(*p == dCell->cellName) 
		return 0;
	return -1;
}

typedef struct{
	int objId;
	// this is set if all are forced to match this obj
	nameData *obj;
	
	// otherwise elab needs to match each of these nameData*
	linkedList assocObjs;	
} objHolder;

// check both obj match (for trans,req,desobj)
int objSearch(void *param,void *data){

	int *p = param;
	objHolder *dHolder = data;

	if(*p == dHolder->objId) 
		return 0;
	return -1;
}

// check Sym
void checkSym(rootData *rdata,linkedList symNameList){
	
	void *test;
	int i,n;
	
	// symbol
	linkedList symLists = rdata->symLists;
	symListInfo **listInfo = toArrayLinked(symLists);
	int listSize = sizeLinked(symLists);
	
	for(i=0;i<listSize;i++){
		symListInfo *curInfo = listInfo[i];
		int nameId = curInfo->nameId;
		
		test = getLinked(symNameList,symNameSearch,&nameId);
		if(test){
			if(nameId)
				printf("Error: Sym Name %s Not Unique.\n",
					getStringSym(nameId));
			else
				printf("Error: More Than One Generic Sym.\n");
			endError();
		}
		addTailLinked(symNameList,curInfo);
		
		int **symbols = toArrayLinked(curInfo->symbols);
		int len = sizeLinked(curInfo->symbols);
		
		linkedList upToSymList = createLinked(Malloc,Free);
		for(n=0;n<len;n++){
			int *symbolP = symbols[n];
			test = getLinked(upToSymList,intSearch,symbolP);
			
			if(test){
				if(nameId)
					printf("Error: Sym %s In %s Not Unique.\n",
						getStringSym(*symbolP),getStringSym(nameId));
				else
					printf("Error: Sym %s In Generic Not Unique.\n",
						getStringSym(*symbolP));				
				endError();
			}
			addTailLinked(upToSymList,symbolP);
		}
		destroyLinked(upToSymList,NULL);
	}
}

// check Board
void checkBoard(rootData *rdata,linkedList symNameList,linkedList boardCellList,linkedList objList){

	void *test;
	int x,y;

	// board
	treeNode *boardNode = rdata->boardNode;
	setData *boardSet = boardNode->data;
	
	cellData **cells = boardSet->setVars;
	int boardHeight = boardSet->height;
	int boardWidth = boardSet->width;
	
	// print board cells
	for(y=0;y<boardHeight;y++){
		for(x=0;x<boardWidth;x++){

			cellData *cd = cells[y*boardWidth+x];
			if(!cd)
				continue;

			int name = cd->cellName;
			int symName = cd->symListName;
			
			symListInfo *symInfo = getLinked(symNameList,symNameSearch,&symName);
			if(!symInfo){
				printf("Error: Symbol List Nonexistant for Board Cell %s.\n",
					getStringSym(name));
				endError();
			}

			// enter in symbol-list
			cd->symList = symInfo->symbols;

			test = getLinked(boardCellList,cellSearch,&name);
			if(test){
				printf("Error: Board Cell %s Not Unique.\n",
					getStringSym(name));
				endError();
			}
			addTailLinked(boardCellList,cd);
		}
	}
	
	// create obj
	nameData *objName = Malloc(sizeof(nameData));
	objName->nameId = addSymbol("Board");
	objName->objId = addSymbol("Board");
	objName->elabNum = 0;
	objName->set = boardSet;

	objHolder *oh = Malloc(sizeof(objHolder));
	oh->objId = objName->objId;
	oh->obj = objName;
	oh->assocObjs = NULL;
	addTailLinked(objList,oh);
}

// load symlist into obj
void updateObj(nameData *name,linkedList symNameList,linkedList boardCellList){
	
	int x,y;
	
	int id = name->objId;
	setData *set = name->set;
	cellData **cellSet = set->setVars;
	int height = set->height;
	int width = set->width;
	
	for(y=0;y<height;y++){
		for(x=0;x<width;x++){

			cellData *cell = cellSet[y*width+x];
			if(!cell)
				continue;

			int symName = cell->symListName;
			int cellName = cell->cellName;

			symListInfo *symInfo = getLinked(symNameList,symNameSearch,&symName);
			if(!symInfo){
				printf("Error: Symbol List Nonexistant for Obj %s Cell %s.\n",
					getStringSym(id),getStringSym(cellName));
				endError();
			}
			cell->symList = symInfo->symbols;
		}
	}
}

// create obj list item from desobj or alldif
nameData *createObj(nameData *name,linkedList boardCellList){
	
	int x,y;
	int desObjObjId = name->objId;
	
	setData *desObjSet = name->set;
	manyData **manySet = desObjSet->setVars;
	int desObjHeight = desObjSet->height;
	int desObjWidth = desObjSet->width;
	
	cellData **newVars = Malloc(sizeof(cellData)*desObjHeight*desObjWidth);
	
	for(y=0;y<desObjHeight;y++){
		for(x=0;x<desObjWidth;x++){		
				
			manyData *many = manySet[y*desObjWidth+x];
			if(!many){
				newVars[y*desObjWidth+x] = NULL;
				continue;
			}

			int *cellNameP = peekLinked(many->brackVars);
			cellData *cell = getLinked(boardCellList,cellSearch,cellNameP);
			if(!cell){
				printf("Error: Board Cell %s In %s:%s Does Not Exist\n",
					getStringSym(*cellNameP),getStringSym(name->nameId),getStringSym(name->objId));
				endError();
			}

			// new obj cell mimics board cell
			cellData *newCell = Malloc(sizeof(cellData));
			newCell->symList = cell->symList;
			newCell->symListName = cell->symListName;
			newCell->cellName = cell->cellName;
			newCell->numSpaceBef = 0;
			
			newVars[y*desObjWidth+x] = newCell;
		}
	}

	setData *newSet = Malloc(sizeof(setData));
	newSet->height = desObjHeight;
	newSet->width = desObjWidth;
	newSet->setVars = newVars;

	nameData *objName = Malloc(sizeof(nameData));
	objName->nameId = desObjObjId;
	objName->objId = desObjObjId;
	objName->elabNum = 0;
	objName->set = newSet;

	return objName;
}

// check Obj, DesObj
void checkObj(rootData *rdata,linkedList symNameList,linkedList boardCellList,linkedList objList){

	linkedList names;
	void *test;
	int x,y,i;
	
	// obj
	linkedList nodes = rdata->objNodes;
	treeNode **vars = toArrayLinked(nodes);
	int size = sizeLinked(nodes);
	
	for(i=0;i<size;i++){
		treeNode *node = vars[i];
		nameData *name = node->data;
		int objId = name->objId;
		
		test = getLinked(objList,objSearch,&objId);
		if(test){
			printf("Error: Object %s Not Unique.\n",
				getStringSym(objId));
			endError();
		}
		updateObj(name,symNameList,boardCellList);
		
		objHolder *oh = Malloc(sizeof(objHolder));
		oh->objId = objId;
		oh->obj = name;
		oh->assocObjs = NULL;
		addTailLinked(objList,oh);
	}
	
	// may need to create implicitely defined object
	// desobj
	nodes = rdata->desObjNodes;
	vars = toArrayLinked(nodes);
	size = sizeLinked(nodes);
	
	names = createLinked(Malloc,Free);
	for(i=0;i<size;i++){
		treeNode *node = vars[i];
		nameData *name = node->data;

		int desObjObjId = name->objId;
		setData *desObjSet = name->set;

		manyData **manySet = desObjSet->setVars;
		int desObjHeight = desObjSet->height;
		int desObjWidth = desObjSet->width;

		// check for object, if it does not exist, create it
		objHolder *oh = getLinked(objList,objSearch,&desObjObjId);
		if(!oh){
			oh = Malloc(sizeof(objHolder));
			oh->objId = desObjObjId;
			oh->obj = NULL;
			oh->assocObjs = createLinked(Malloc,Free);
			addTailLinked(objList,oh);
		}

		// strong obj means it was created by Obj and must be followed exactly (symbols aswell)
		nameData *objName = oh->obj;
		int isStrongObj = 1;

		if(!objName){
			objName = createObj(name,boardCellList);
			addTailLinked(oh->assocObjs,objName);
			isStrongObj = 0;
		}

		setData *objSet = objName->set;
		cellData **cellSet = objSet->setVars;
		int objHeight = objSet->height;
		int objWidth = objSet->width;

		if(desObjHeight != objHeight || desObjWidth != objWidth){
			printf("Error: DesObj %s:%s Does Not Match Object Size.\n",
				getStringSym(name->nameId),getStringSym(name->objId));
			endError();
		}

		for(y=0;y<desObjHeight;y++){
			for(x=0;x<desObjWidth;x++){
				
				manyData *many = manySet[y*desObjWidth+x];
				cellData *objCell = cellSet[y*desObjWidth+x];

				if((!many && objCell) || (many && !objCell)){
					printf("Error: DesObj %s:%s Does Not Match Object Shape.\n",
						getStringSym(name->nameId),getStringSym(name->objId));
					endError();
				}

				if(!many)
					continue;

				int *cellNameP = peekLinked(many->brackVars);
				cellData *boardCell = getLinked(boardCellList,cellSearch,cellNameP);
				if(!boardCell){
					printf("Error: Board Cell %s In %s:%s Does Not Exist.\n",
						getStringSym(*cellNameP),getStringSym(name->nameId),getStringSym(name->objId));
					endError();
				}
				
				if(isStrongObj && boardCell->symListName != objCell->symListName){
					printf("Error: DesObj %s:%s Cell %s Does Not Match Object Symbol List.\n",
						getStringSym(name->nameId),getStringSym(name->objId),getStringSym(*cellNameP));
					endError();
				}
			}
		}

		test = getLinked(names,fullSearch,name);
		if(test){
			printf("Error: Describe Object %s:%s Not Unique.\n",
				getStringSym(name->nameId),getStringSym(name->objId));
			endError();
		}
		addTailLinked(names,name);
	}
	destroyLinked(names,NULL);
}

void checkAllDif(rootData *rdata,linkedList boardCellList){

	linkedList nodes = rdata->allDifNodes;
	treeNode **vars = toArrayLinked(nodes);
	int size = sizeLinked(nodes);
	
	int i;
	for(i=0;i<size;i++){
		treeNode *node = vars[i];
		nameData *name = node->data;
		createObj(name,boardCellList);
	}
}

typedef struct {
	int symListId;
	int tempId;
	
	// this indicates it actually exists somewhere in the Elab
	int instance;
} tempVar;

// matches tempId
int tempSearch(void *param,void *data){
	
	int *p = param;
	tempVar *dTemp = data;
	
	if(*p == dTemp->tempId)
		return 0;
	return -1;
}

// check connecter
// check tempvar does not appear ever as symbol
void checkTemp(char *elabTypeName,int elabNameId,int elabObjId,int tempVarName,int mySymListName,linkedList mySymList,
	linkedList allSymLists,linkedList tempVars,int isInstance){

	// test if this temp has been used elsewhere, if not, it should be created
	tempVar *temp = getLinked(tempVars,tempSearch,&tempVarName);
	if(temp){
		if(!temp->instance)
			temp->instance = 1;
	}
	else{
		temp = Malloc(sizeof(tempVar));
		temp->symListId = mySymListName;
		temp->tempId = tempVarName;
		temp->instance = isInstance;
		addTailLinked(tempVars,temp);
	}
	
	// check this tempVar is not named for any symbol anywhere
	symListInfo **infoArr = toArrayLinked(allSymLists);
	int size = sizeLinked(allSymLists);
		
	int i;
	for(i=0;i<size;i++){
		symListInfo *info = infoArr[i];
		linkedList symbols = info->symbols;

		// determine if it is our symbol
		void *test = getLinked(mySymList,intSearch,&tempVarName);
		if(test)
			continue;

		test = getLinked(symbols,intSearch,&tempVarName);
		if(test){
			printf("Error: %s %s:%s Temporary Variable %s Can't Have Same Name As A Symbol.\n",
				elabTypeName,getStringSym(elabNameId),getStringSym(elabObjId),getStringSym(tempVarName));
			endError();
		}
	}

	int getSymListName = temp->symListId;
	
	// broken connector
	if(getSymListName != mySymListName){
		printf("Error: %s %s:%s Temporary Variable %s Connects Symbol List %s To %s.\n",
			elabTypeName,getStringSym(elabNameId),getStringSym(elabObjId),getStringSym(tempVarName),
			getStringSym(getSymListName),getStringSym(mySymListName));
		endError();
	}
}

void addVars(char *elabTypeName,int elabNameId,int elabObjId,linkedList toAdd,int mySymListName,linkedList mySymList,linkedList allSymLists,linkedList tempVars){
	
	int i;
	int **vars = toArrayLinked(toAdd);
	int size = sizeLinked(toAdd);
	
	for(i=0;i<size;i++){
		int *tempP = vars[i];
		int temp = *tempP;

		// if it is in the cell's symbol list, it is not a tempVar and does not need to be checked
		int *testSym = getLinked(mySymList,intSearch,&temp);
		if(!testSym)
			checkTemp(elabTypeName,elabNameId,elabObjId,temp,mySymListName,mySymList,allSymLists,tempVars,0);
	}
}

// store temp, tempVars contains tempVar
void checkElabSpecObj(char *elabTypeName,int elabNameId,int elabObjId,setData *nameSet,linkedList allSymLists,nameData *obj,linkedList tempVars){
	
	int x,y;
	
	setData *objSet = obj->set;
	int objWidth = objSet->height;
	int objHeight = objSet->width;
	cellData **cells = objSet->setVars;
	
	int nameWidth = nameSet->height;
	int nameHeight = nameSet->width;
	elabData **elabs = nameSet->setVars;

	if(nameWidth != objWidth || nameHeight != objHeight){
		printf("Error: %s %s:%s Does Not Match Object Size.\n",
			elabTypeName,getStringSym(elabNameId),getStringSym(elabObjId));
		endError();
	}
	
	for(y=0;y<nameHeight;y++){
		for(x=0;x<nameWidth;x++){
			elabData *elab = elabs[y*nameWidth + x];
			cellData *cell = cells[y*nameWidth + x];
			
			if((elab && !cell) || (!elab && cell)){
				printf("Error: %s %s:%s Does Not Match Object Shape.\n",
					elabTypeName,getStringSym(elabNameId),getStringSym(elabObjId));
				endError();
			}
			
			if(!elab)
				continue;

			int tempVarName = elab->tempVarName;
			linkedList negVars = elab->negVars;
			linkedList posVars = elab->posVars;
			
			linkedList symList = cell->symList;
			int symListName = cell->symListName;
			
			// if these is an instance
			if(tempVarName){
				
				// if this is a symbol, it cannot have colon constraint
				int *testSym = getLinked(symList,intSearch,&tempVarName);
				if(testSym){
					if(sizeLinked(negVars) > 0 || sizeLinked(posVars) > 0){
						printf("Error: %s %s:%s Symbol %s Cannot Have Additional Constraints.\n",
							elabTypeName,getStringSym(elabNameId),getStringSym(elabObjId),getStringSym(tempVarName));
						endError();
					}
					continue;
				}
				
				// check connection is valid and not from any other symbol
				checkTemp(elabTypeName,elabNameId,elabObjId,tempVarName,symListName,symList,allSymLists,tempVars,1);
			}
			
			// go through posVars and negVars to add tempVar
			if(negVars)
				addVars(elabTypeName,elabNameId,elabObjId,negVars,symListName,symList,allSymLists,tempVars);
			if(posVars)
				addVars(elabTypeName,elabNameId,elabObjId,posVars,symListName,symList,allSymLists,tempVars);
		}
	}
}

// search for blank instance
int instBlankSearch(void *param,void *data){
	
	tempVar *dTemp = data;
	if(dTemp->instance == 0)
		return 0;
	return -1;
}

// check that all tempVars are instantiated and none are just in () 
void checkTempInst(char *elabTypeName,int elabNameId,int elabObjId,linkedList tempVars){

	tempVar *tv = getLinked(tempVars,instBlankSearch,NULL);
	if(tv){
		printf("Error: %s %s:%s Symbol %s Only Exists Within Parentheses.\n",
			elabTypeName,getStringSym(elabNameId),getStringSym(elabObjId),getStringSym(tv->tempId));
		endError();
	}
}

// elab details
void checkElabDet(char *elabTypeName,int elabNameId,int elabObjId,setData *nameSetStart,setData *nameSetEnd,
			linkedList allSymLists,linkedList objList,nodeStages *stages){
	
	int i;
	
	if(stages && (stages->start < 0 || stages->end > numStagesGlobal)){
		printf("Error: %s %s:%s Stage Outside Bounds.\n",
			elabTypeName,getStringSym(elabNameId),getStringSym(elabObjId));
		endError();
	}

	objHolder *oh = getLinked(objList,objSearch,&elabObjId);
	if(!oh){
		printf("Error: %s %s Invalid Object.\n",
			elabTypeName, getStringSym(elabNameId));
		endError();
	}

	nameData *obj = oh->obj;
	linkedList assocObjs = oh->assocObjs;
	
	if(obj){
		linkedList tempVars = createLinked(Malloc,Free);
		checkElabSpecObj(elabTypeName,elabNameId,elabObjId,nameSetStart,allSymLists,obj,tempVars);
		if(nameSetEnd)
			checkElabSpecObj(elabTypeName,elabNameId,elabObjId,nameSetEnd,allSymLists,obj,tempVars);
		checkTempInst(elabTypeName,elabNameId,elabObjId,tempVars);
		destroyLinked(tempVars,singleFree);
		return;
	}
	
	nameData **objArr = toArrayLinked(assocObjs);
	int size = sizeLinked(assocObjs);
	
	for(i=0;i<size;i++){
		nameData *obj = objArr[i];

		linkedList tempVars = createLinked(Malloc,Free);
		checkElabSpecObj(elabTypeName,elabNameId,elabObjId,nameSetStart,allSymLists,obj,tempVars);
		if(nameSetEnd)
			checkElabSpecObj(elabTypeName,elabNameId,elabObjId,nameSetEnd,allSymLists,obj,tempVars);
		checkTempInst(elabTypeName,elabNameId,elabObjId,tempVars);
		destroyLinked(tempVars,singleFree);
	}
}

void checkReq(rootData *rdata,linkedList allSymLists,linkedList objList){
	
	int i;
	linkedList nodes = rdata->reqNodes;
	treeNode **vars = toArrayLinked(nodes);
	int size = sizeLinked(nodes);
	
	linkedList names = createLinked(Malloc,Free);
	for(i=0;i<size;i++){
		treeNode *node = vars[i];
		nameData *name = node->data;
		
		int nameId = name->nameId;
		int objId = name->objId;
		setData *set = name->set;
		
		// confirm it matches its object
		checkElabDet("Require",nameId,objId,set,NULL,allSymLists,objList,node->stages);

		void *test = getLinked(names,fullSearch,name);
		if(test){
			printf("Error: Require %s:%s Not Unique.\n",
				getStringSym(nameId),getStringSym(objId));
			endError();
		}
		addTailLinked(names,name);
	}
	destroyLinked(names,NULL);
}

void checkOpt(rootData *rdata,linkedList allSymLists,linkedList objList){
	
	int i;
	linkedList nodes = rdata->optNodes;
	treeNode **vars = toArrayLinked(nodes);
	int size = sizeLinked(nodes);
	
	for(i=0;i<size;i++){
		treeNode *node = vars[i];
		nameData *name = node->data;
		
		int nameId = name->nameId;
		int objId = name->objId;
		setData *set = name->set;
		
		// confirm it matches its object
		checkElabDet("Option",nameId,objId,set,NULL,allSymLists,objList,node->stages);
	}
}

void checkTrans(rootData *rdata,linkedList allSymLists,linkedList objList){

	int i;
	linkedList nodes = rdata->transNodes;
	treeNode **vars = toArrayLinked(nodes);
	int size = sizeLinked(nodes);
	
	linkedList names = createLinked(Malloc,Free);
	for(i=0;i<size;i++){
		treeNode *node = vars[i];
		transData *name = node->data;
		
		int nameId = name->transId;
		int objId = name->objId;
		setData *startSet = name->startData;
		setData *endSet = name->endData;
		
		// confirm it matches its object
		checkElabDet("Transform",nameId,objId,startSet,endSet,allSymLists,objList,node->stages);

		void *test = getLinked(names,fullSearch,name);
		if(test){
			printf("Error: Transform %s:%s Not Unique.\n",
				getStringSym(nameId),getStringSym(objId));
			endError();
		}
		addTailLinked(names,name);
	}
	destroyLinked(names,NULL);
}

void checkStartEnd(rootData *rdata,linkedList allSymLists,linkedList objList){

	// Start
	treeNode *node = rdata->startNode;
	if(!node)
		return;
	nameData *name = node->data;
	name->nameId = addSymbol("Start");
	name->objId = addSymbol("Board");
		
	int nameId = name->nameId;
	int objId = name->objId;
	setData *set = name->set;
	
	checkElabDet("Setup",nameId,objId,set,NULL,allSymLists,objList,NULL);
	
	// End
	node = rdata->endNode;
	name = node->data;
	name->nameId = addSymbol("End");
	name->objId = addSymbol("Board");
		
	nameId = name->nameId;
	objId = name->objId;
	set = name->set;
	
	checkElabDet("Setup",nameId,objId,set,NULL,allSymLists,objList,NULL);
}

/***************** Post-Process AST *************/

// for board symlists
int getSym(void *param,void *data){
	
	int *namePoint = param;
	int name = *namePoint;
	symListInfo *info = data;
	
	if(name == info->nameId)
		return 0;
	return -1;
}

// place corresponding sym-list into each board-cell
void completeBoard(rootData *rdata){
		
	treeNode *boardNode = rdata->boardNode;
	setData *boardSet = boardNode->data;

	linkedList symLists = rdata->symLists;

	// space . in board
	linkedList space = boardNode->spaces;
	
	cellData **cells = boardSet->setVars;
	int height = boardSet->height;
	int width = boardSet->width;

	int *num;
	int x,y;
	for(y=0;y<height;y++){
		for(x=0;x<width;x++){

			cellData *cd = cells[y*width+x];			
			if(!cd)
				continue;

			// space
			num = popLinked(space);
			int symListName = cd->symListName;
			symListInfo *info = getLinked(symLists,getSym,&symListName);
			cd->symList = info->symbols;
			cd->numSpaceBef = *num;
			Free(num);
		}
	}
}

// object description (Board)
void addBoard(rootData *rdata){

	treeNode *boardNode = rdata->boardNode;
	setData *boardSet = boardNode->data;
	
	int height = boardSet->height;
	int width = boardSet->width;
	cellData **setVars = boardSet->setVars;
	
	// turn from charset to manyset for DesObj
	manyData **many = Malloc(sizeof(manyData)*width*height);
	int x,y;
	int *add;

	for(y=0;y<height;y++){
		for(x=0;x<width;x++){

			many[y*width + x] = NULL;
			cellData *cd = setVars[y*width + x];
			if(!cd)
				continue;

			add = Malloc(sizeof(int));
			*add = setVars[y*width + x]->cellName;
			
			manyData *hold = Malloc(sizeof(manyData));
			hold->brackVars = createLinked(Malloc,Free);
			addTailLinked(hold->brackVars,add);
			
			many[y*width + x] = hold;
		}
	}
	
	setData *desObjBoardSet = Malloc(sizeof(setData));
	desObjBoardSet->height = height;
	desObjBoardSet->width = width;
	desObjBoardSet->setVars = many;

	// board object
	int boardId = addSymbol("Board");
	nameData *desObj = Malloc(sizeof(nameData));
	desObj->nameId = boardId;
	desObj->objId = boardId;
	desObj->set = desObjBoardSet;
	
	treeNode *tn = Malloc(sizeof(treeNode));
	tn->type = desObjType;
	tn->data = desObj;
	addTailLinked(rdata->desObjNodes,tn);
}

// for each DesObj insert its cellData
void symListToCells(rootData *rdata,linkedList desObjNodes){
	
	// board
	treeNode *boardNode = rdata->boardNode;
	setData *boardSet = boardNode->data;
	
	cellData **boardCell = boardSet->setVars;
	int boardHeight = boardSet->height;
	int boardWidth = boardSet->width;
	
	// desobj 
	int desObjWidth = sizeLinked(desObjNodes);
	treeNode **desObjArray = toArrayLinked(desObjNodes);
	
	int boardX,boardY,desX,desY,i,n;
	for(i=0;i<desObjWidth;i++){

		treeNode *desObj = desObjArray[i];
		nameData *objData = desObj->data;

		// go through each cell in desObj
		setData *desSet = objData->set;
		manyData **desObjMany = desSet->setVars;
		int desHeight = desSet->height;
		int desWidth = desSet->width;
		
		for(desY=0;desY<desHeight;desY++){
			for(desX=0;desX<desWidth;desX++){

				// in manyData
				manyData *many = desObjMany[desY*desWidth + desX];
				if(!many)
					continue;

				linkedList nameList = many->brackVars;
				int **nameArr = toArrayLinked(nameList);
				int nameSize = sizeLinked(nameList);

				for(n=0;n<nameSize;n++){

					int desCellName = *nameArr[n];
				
					// find the cell-name in the board
					for(boardY=0;boardY<boardHeight;boardY++){
						for(boardX=0;boardX<boardWidth;boardX++){
							cellData *cd = boardCell[boardY*boardWidth + boardX];
							if(!cd)
								continue;

							int boardCellName = cd->cellName;
							if(boardCellName == desCellName){
								many->symList = cd->symList;
							}
						}
					}
				}
			}
		}
	}
}

// complete AST
void postProc(rootData *rdata){

	completeBoard(rdata);
	addBoard(rdata);
	
	linkedList desObjNodes = rdata->desObjNodes;
	linkedList allDifNodes = rdata->allDifNodes;
	
	symListToCells(rdata,desObjNodes);
	symListToCells(rdata,allDifNodes);
}

/***************** Memory Free *************/

// free elab data
void remElab(setData *set){

	int i;
	int size = set->height * set->width;
	elabData **elabs = set->setVars;
		
	for(i=0;i<size;i++){
		
		elabData *elab = elabs[i];
		if(!elab)
			continue;

		if(elab->posVars)
			destroyLinked(elab->posVars,singleFree);
		if(elab->negVars)
			destroyLinked(elab->negVars,singleFree);
		Free(elab);
	}
	
	Free(elabs);
	Free(set);
}

// free sub tree
void remSubTree(void *inData){
	
	int size,i;

	treeNode *node = inData;
	void *data = node->data;
	nodeType type = node->type;

	if(type == boardType || type == objType){

		setData *set = data;
		if(type == objType){
			nameData *name = data;
			set = name->set;
			Free(name);
		}

		size = (set->height) * (set->width);
		cellData **cells = set->setVars;
		
		// symlist is just a pointer to symbols
		for(i=0;i<size;i++)
			if(cells[i])		
				Free(cells[i]);

		Free(cells);
		Free(set);
	}
	
	if(type == startType || type == endType || type == reqType || type == optType){
		nameData *name = data;
		remElab(name->set);
		Free(name);
	}
	
	if(type == transType || type == transSimType){
		transData *trans = data;
		remElab(trans->startData);
		remElab(trans->endData);
		Free(trans);
	}
	
	if(type == desObjType){
		nameData *name = data;
		setData *set = name->set;
		size = (set->height) * (set->width);
		manyData **manys = set->setVars;
		
		// symlist is just a pointer to symbols
		for(i=0;i<size;i++){
			manyData *many = manys[i];
			if(!many)
				continue;

			destroyLinked(many->brackVars,singleFree);
			Free(many);
		}
		Free(manys);
		Free(set);
		Free(name);
	}
	
	if(type == boardType)
		destroyLinked(node->spaces,singleFree);

	if(type == reqType || type == optType || type == transType || type == transSimType)
		Free(node->stages);

	Free(node);
}

// free all from AST from arch
// this is unnessary as the program will need the AST until the program
// is over and all memory is relinquished, but clearing it is good practice
void freeArch(treeNode *rootNode){
	
	rootData *root = rootNode->data;

	// sym	
	linkedList syms = root->symLists;
	symListInfo *symInfo;
	while((symInfo = popLinked(syms))){
		linkedList symbols = symInfo->symbols;
		destroyLinked(symbols,singleFree);
		Free(symInfo);
	}
	destroyLinked(syms,NULL);
	
	remSubTree(root->boardNode);
	if(root->startNode)
		remSubTree(root->startNode);
	if(root->endNode)
		remSubTree(root->endNode);
	
	destroyLinked(root->objNodes,remSubTree);
	destroyLinked(root->desObjNodes,remSubTree);
	destroyLinked(root->reqNodes,remSubTree);
	destroyLinked(root->optNodes,remSubTree);
	destroyLinked(root->transNodes,remSubTree);
	
	Free(root);
	Free(rootNode);
}

/***************** Main Debugger *************/

// must check Sym, Board, Obj, DesObj, Opt, Req, Trans(Sim), Start, End
void compilerDebug(rootData *rdata){

	linkedList symNameList = createLinked(Malloc,Free);
	linkedList boardCellList = createLinked(Malloc,Free);
	linkedList objList = createLinked(Malloc,Free);
	
	checkSym(rdata,symNameList);
	checkBoard(rdata,symNameList,boardCellList,objList);
	checkStartEnd(rdata,symNameList,objList);

	checkObj(rdata,symNameList,boardCellList,objList);
	checkAllDif(rdata,boardCellList);

	checkReq(rdata,symNameList,objList);
	checkOpt(rdata,symNameList,objList);
	checkTrans(rdata,symNameList,objList);

	// only has pointers
	destroyLinked(symNameList,NULL);
	destroyLinked(boardCellList,NULL);
	
	objHolder *remHold;
	while((remHold = popLinked(objList))){
		int objId = remHold->objId;
		nameData *obj = remHold->obj;
		linkedList assocObjs = remHold->assocObjs;
		
		if(objId == addSymbol("Board"))
			Free(obj);
		
		// delete all of assocObjs
		if(assocObjs){
			nameData *name;
			while((name = popLinked(assocObjs))){

				setData *setD = name->set;
				cellData **cells = setD->setVars;
				int size = (setD->height) * (setD->width);
				int i;

				for(i=0;i<size;i++)
					if(cells[i])
						Free(cells[i]);

				Free(cells);
				Free(setD);
				Free(name);
			}
			destroyLinked(assocObjs,NULL);
		}

		Free(remHold);
	}
	destroyLinked(objList,NULL);
}
