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

// this file does the main processing to compile language to cnf and 
// turn cnf into human readable form

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tbl.h"
#include "structs.h"
#include "arch.h"
#include "debug.h"
#include "req.h"
#include "var.h"
#include "../utils/linkedlist.h"
#include "../utils/gendebug.h"

// a trans must be created for each desObj that describes it because the board cells change for each desObj
linkedList expandTrans(rootData *rdata){

	int i,j;
	linkedList fullTransList = createLinked(Malloc,Free);
	
	// trans
	linkedList transNodes = rdata->transNodes;
	int transWidth = sizeLinked(transNodes);
	treeNode **transArray = toArrayLinked(transNodes);
	
	// desObj
	linkedList desObjNodes = rdata->desObjNodes;
	int desObjWidth = sizeLinked(desObjNodes);
	treeNode **desObjArray = toArrayLinked(desObjNodes);
	
	for(i=0;i<transWidth;i++){
		treeNode *trans = transArray[i];
		transData *td = trans->data;
		int transId = td->transId;		
		int transObjId = td->objId;
		
		// collect all object descriptions with same object id as this transition
		for(j=0;j<desObjWidth;j++){
			
			treeNode *desObj = desObjArray[j];
			nameData *objData = desObj->data;
			int desObjId = objData->objId;

			if(transObjId == desObjId){
				
				tempTransVar *var = Malloc(sizeof(tempTransVar));
				var->transId = transId;
				var->startData = td->startData;
				var->endData = td->endData;

				var->objId = objData->objId;
				var->desObjId = objData->nameId;
				var->desObjSet = objData->set;
				var->stages = trans->stages;
				var->isSim = 0;
				if(trans->type == transSimType)
					var->isSim = 1;
				pushLinked(fullTransList,var);
			}
		}
	}
	return fullTransList;
}

// list of sat variables
linkedList createVarList(rootData *rdata,linkedList fullTransNodes){
	
	indexList *varList = createVarIndex();
	
	// board
	treeNode *boardNode = rdata->boardNode;
	setData *boardSet = boardNode->data;
	int boardWidth = boardSet->width;
	int boardHeight = boardSet->height;
	cellData **boardVars = boardSet->setVars;
	int y,x,i,n;
	
	for(y=0;y<boardHeight;y++){
		for(x=0;x<boardWidth;x++){

			if(!boardVars[y*boardWidth+x]) 
				continue;

			cellData *cell = boardVars[y*boardWidth+x];
			int cellName = cell->cellName;
			linkedList symList = cell->symList;

			int symWidth = sizeLinked(symList);
			int **symArray = toArrayLinked(symList);
			
			// since there are only two symbols, symbol and not symbol are used as variables
			if(symWidth > 2){
				for(i=0;i<symWidth;i++){
					int symId = *symArray[i];
				
					for(n=0;n<numStages;n++){
						createSymCellVar(varList,symId,cellName,x,y,n,NULL);
					}
				}
			}
			else{
				for(n=0;n<numStages;n++){
					int symId = *symArray[0];
					varData *vdat = createSymCellVar(varList,symId,cellName,x,y,n,NULL);
					symId = *symArray[1];
					createSymCellVar(varList,symId,cellName,x,y,n,vdat);
				}
			}
		}
	}
	
	// trans
	int transWidth = sizeLinked(fullTransNodes);
	tempTransVar **transArray = toArrayLinked(fullTransNodes);

	for(i=0;i<transWidth;i++){
		tempTransVar *data = transArray[i];
		int transId = data->transId;
		int transObjId = data->objId;
		int desObjId = data->desObjId;
		
		// there is a variable associated with each transition-stage
		nodeStages *stages = data->stages;
		for(n=stages->start;n<stages->end-1;n++){
			createTransVar(varList,transId,transObjId,desObjId,n);
		}
	}
	
	// used
	for(y=0;y<boardHeight;y++){
		for(x=0;x<boardWidth;x++){

			if(!boardVars[y*boardWidth+x])
				continue;
			cellData *cell = boardVars[y*boardWidth+x];
			
			for(n=0;n<numStages-1;n++){
				createUsedVar(varList,cell->cellName,x,y,n);
			}
		}
	}
	
	return varList;
}

clauseVarData *createClauseVar(varData *var,int neg){

	assert(var,"Var Is Null\n");
	clauseVarData *clauseVar = Malloc(sizeof(clauseVarData));
	clauseVar->negate = neg;
	clauseVar->data = var;
	return clauseVar;
}

void startEndClauses(rootData *rdata,indexList *varList,linkedList clauseList){
	
	if(!rdata->startNode)
		return;

	linkedList desObjNodes = rdata->desObjNodes;

	elabFullData elabTemp; 
	elabFullData *elab = &elabTemp;

	// start
	treeNode *startNode = rdata->startNode;
	nameData *startData = startNode->data;	
	
	elab->type = startType;
	elab->elabId = addSymbol("Board");
	elab->objId = addSymbol("Board");
	elab->startData = startData->set;
	elab->endData = NULL;
	elab->stages = NULL;
	
	elabClauses(elab,desObjNodes,varList,clauseList);

	// end
	treeNode *endNode = rdata->endNode;
	nameData *endData = endNode->data;	
	
	elab->type = endType;
	elab->elabId = addSymbol("Board");
	elab->objId = addSymbol("Board");
	elab->startData = endData->set;
	elab->endData = NULL;
	elab->stages = NULL;

	elabClauses(elab,desObjNodes,varList,clauseList);
}

void stdInfraTrans(rootData *rdata,indexList *varList,linkedList clauseList,linkedList fullTransNodes,int allowBlankTrans){
	
	int i,n;

	// at most, least one trans/stage
	int transWidth = sizeLinked(fullTransNodes);
	tempTransVar **transArray = toArrayLinked(fullTransNodes);

	// can have an empty state with zero transitions	
	// at most one

	for(n=0;n<numStages-1;n++){

		linkedList *transList = createLinked(Malloc,Free);
		for(i=0;i<transWidth;i++){
			
			tempTransVar *tv = transArray[i];
			int desObjId = tv->desObjId;
			int transId = tv->transId;
			nodeStages *stages = tv->stages;
		
			if(tv->isSim)
				continue;
			
			// stages are inclusive between start and end for both
			int start = stages->start;
			int end = stages->end;
			
			if(n<start || n>=end-1)
				continue;
		
			varData *var = getTransVar(varList,transId,desObjId,n);
			assert(var,"Trans Failed");
			addTailLinked(transList,var);
		}
		
		if(!allowBlankTrans)
			atLeastOne(transList,clauseList);

		// possible to have a stage with no trans if allowBlankTrans is 0
		atMostOne(transList,clauseList);
		destroyLinked(transList,NULL);
	}
}

// log base 2
int log2Int(int num){

	int logVal = 0;
	int expo = 1;
	while(expo < num){
		expo = expo*2;
		logVal++;
	}
	return logVal;
}

void advInfraTrans(rootData *rdata,indexList *varList,linkedList clauseList,linkedList fullTransNodes){
	
	int x,i,n;
	linkedList clause;
	clauseVarData *clauseVar;
	
	// at most, least one trans/stage
	int transWidth = sizeLinked(fullTransNodes);
	tempTransVar **transArray = toArrayLinked(fullTransNodes);
	
	int logVal = log2Int(transWidth);
	
	// can have an empty state with zero transitions
	// at most one
	for(i=0;i<transWidth;i++){
		
		tempTransVar *tv = transArray[i];
		int desObjId = tv->desObjId;
		int transId = tv->transId;
		nodeStages *stages = tv->stages;

		if(tv->isSim)
			continue;
		
		for(n=0;n<numStages-1;n++){

			if(n < stages->start || n > stages->end)
				continue;
			
			varData *trans = getTransVar(varList,transId,desObjId,n);
			assert(trans,"Trans Failed");

			int setPart = i+1;

			// set the vars to the corresponding trans
			for(x=0;x<=logVal;x++){
				
				clause = createLinked(Malloc,Free);
				
				varData *part = getTransPartVar(varList,x,n);
				if(!part)
					part = createTransPartVar(varList,x,n);
				
				clauseVar = createClauseVar(trans,1);
				addTailLinked(clause,clauseVar);
				
				int isNeg = !(setPart % 2);
				setPart = setPart >> 1;

				clauseVar = createClauseVar(part,isNeg);
				addTailLinked(clause,clauseVar);
				
				addTailLinked(clauseList,clause);
			}
		}
	}
}

void infraClauses(rootData *rdata,indexList *varList,linkedList clauseList,linkedList fullTransNodes,int allowAdvTrans,int allowBlankTrans){

	int y,x,i,n;
	
	// clauses from infrastructure
	// at most, least one symbol/cell/stage
	treeNode *boardNode = rdata->boardNode;
	setData *boardSet = boardNode->data;
	
	int boardWidth = boardSet->width;
	int boardHeight = boardSet->height;
	cellData **boardVars = boardSet->setVars;
	
	for(y=0;y<boardHeight;y++){
		for(x=0;x<boardWidth;x++){

			if(!boardVars[y*boardWidth + x])
				continue;

			cellData *cell = boardVars[y*boardWidth + x];
			linkedList symList = cell->symList;
			int symWidth = sizeLinked(symList);
			int **symArray = toArrayLinked(symList);

			for(n=0;n<numStages;n++){
			
				if(symWidth > 2){
				
					// at least, most one variable
					linkedList newVarList = createLinked(Malloc,Free);
					for(i=0;i<symWidth;i++){
						int symId = *symArray[i];
						varData *var = getSymCellVar(varList,x,y,symId,n);
						assert(var,"Var Failed");
						addTailLinked(newVarList,var);
					}
				
					atLeastOne(newVarList,clauseList);
					atMostOne(newVarList,clauseList);
					destroyLinked(newVarList,NULL);
				}
			}
		}
	}
	
	// in cases where there are a lot of trans, it is faster to change the way at-most-one 
	// is performed to matching each to the equivalent of a binary number (series of TransPartVar)
	int transWidth = sizeLinked(fullTransNodes);
	
	if(transWidth > 64 && allowAdvTrans)
		advInfraTrans(rdata,varList,clauseList,fullTransNodes);
	else
		stdInfraTrans(rdata,varList,clauseList,fullTransNodes,allowBlankTrans);
}

void transClauses(rootData *rdata,indexList *varList,linkedList clauseList){

	int i;

	linkedList desObjNodes = rdata->desObjNodes;
	linkedList transNodes = rdata->transNodes;
	int transSize = sizeLinked(transNodes);
	treeNode **transArray = toArrayLinked(transNodes);
	
	elabFullData elabTemp;
	elabFullData *elab = &elabTemp;
	
	for(i=0;i<transSize;i++){
		
		treeNode *transNode = transArray[i];
		transData *transData = transNode->data;
		
		elab->type = transType;
		elab->elabId = transData->transId;
		elab->objId = transData->objId;
		elab->startData = transData->startData;
		elab->endData = transData->endData;
		elab->stages = transNode->stages;
		
		elabClauses(elab,desObjNodes,varList,clauseList);
	}
}

// this sets cellUsedStageN=>N+1 variables when that cell is used in that transition
void setUsedClauses(rootData *rdata,indexList *varList,linkedList clauseList,linkedList fullTransNodes){

	int i,n;
	linkedList clause;
	clauseVarData *clauseVar;
	
	// trans
	int transWidth = sizeLinked(fullTransNodes);
	tempTransVar **transArray = toArrayLinked(fullTransNodes);

	// board
	treeNode *boardNode = rdata->boardNode;
	setData *boardSet = boardNode->data;
	
	int boardWidth = boardSet->width;
	int boardHeight = boardSet->height;
	cellData **boardVars = boardSet->setVars;
	
	int boardX, boardY;
	int desObjX, desObjY;
		
	// for each cellStage used-var	
	// find all transitions that use that cell, put it into the set

	for(boardY=0;boardY<boardHeight;boardY++){
		for(boardX=0;boardX<boardWidth;boardX++){

			if(!boardVars[boardY*boardWidth+boardX])
				continue;
			cellData *boardCell = boardVars[boardY*boardWidth+boardX];
			int boardCellName = boardCell->cellName;

			for(n=0;n<numStages-1;n++){
				
				varData *used = getUsedVar(varList,boardX,boardY,n);
				assert(used,"Used NULL");

				// NOT cellUsedStageN=>N+1 OR tran1StageN=>N+1 OR tran2StageN=>N+1 OR ...
				linkedList transListClause = createLinked(Malloc,Free);
				
				// contains varData
				// this is for saying at most one of these simultaneous trans that use this cell can be used
				linkedList transSimAtMostList = createLinked(Malloc,Free);

				// try to find it in trans
				for(i=0;i<transWidth;i++){

					tempTransVar *trans = transArray[i];

					// if this trans does not occur at this stage, it is not included in list that would indicate cell is used
					nodeStages *stages = trans->stages;
					if(n < stages->start || n > stages->end)
						continue;

					varData *tv = getTransVar(varList,trans->transId,trans->desObjId,n);
					assert(tv,"Trans NULL");				

					// true if the transition operates on board cell (boardX,boardY)
					int transUsesBoardCell = 0;

					// if it is the board, this x,y is used
					setData *dos = trans->desObjSet;

					manyData **desObjSet = dos->setVars;
					int desObjHeight = dos->height;
					int desObjWidth = dos->width;	
						
					for(desObjY=0;desObjY<desObjHeight;desObjY++){
						for(desObjX=0;desObjX<desObjWidth;desObjX++){
			
							if(!desObjSet[desObjY*desObjWidth + desObjX]) 
								continue;
								
							manyData *md = desObjSet[desObjY*desObjWidth + desObjX];
							linkedList brackVars = md->brackVars;
							int *objSymP = peekLinked(brackVars);
							int desObjCellName = *objSymP;

							if(boardCellName == desObjCellName){
								transUsesBoardCell = 1;
							}
						}
					}
					
					// found board cell
					if(transUsesBoardCell){

						clause = createLinked(Malloc,Free);
						clauseVar = createClauseVar(used,0);
						addTailLinked(clause,clauseVar);
						clauseVar = createClauseVar(tv,1);
						addTailLinked(clause,clauseVar);

						assertBool(sizeLinked(clause) != 0,"Empty Clause Used");
						addTailLinked(clauseList,clause);

						clauseVar = createClauseVar(tv,0);
						addTailLinked(transListClause,clauseVar);

						// if it is not a TransSim it is already in an at-most-one
						if(trans->isSim){
							// varData
							addTailLinked(transSimAtMostList,tv);
						}
					}
				}
				
				// connect this trans to this used cell
				clauseVar = createClauseVar(used,1);
				pushLinked(transListClause,clauseVar);

				addTailLinked(clauseList,transListClause);

				// for TransSim
				atMostOne(transSimAtMostList,clauseList);
				destroyLinked(transSimAtMostList,NULL);
			}
		}
	}
}

// this forces the cell to remain the same when cellUsedStageN=>N+1 is not set
void usedClauses(rootData *rdata,indexList *varList,linkedList clauseList,linkedList fullTransNodes){

	int i,n;
	linkedList clause;
	clauseVarData *clauseVar;

	// board
	treeNode *boardNode = rdata->boardNode;
	setData *boardSet = boardNode->data;
	
	int boardWidth = boardSet->width;
	int boardHeight = boardSet->height;
	cellData **boardVars = boardSet->setVars;
	int boardX, boardY;
	
	// for each cellStage used-var	
	// find all transitions that use that cell, put it into the set
	
	for(boardY=0;boardY<boardHeight;boardY++){
		for(boardX=0;boardX<boardWidth;boardX++){

			if(!boardVars[boardY*boardWidth+boardX])
				continue;

			cellData *cell = boardVars[boardY*boardWidth+boardX];
			linkedList symList = cell->symList;
			int symWidth = sizeLinked(symList);
			int **symArray = toArrayLinked(symList);

			for(n=0;n<numStages-1;n++){

				varData *used = getUsedVar(varList,boardX,boardY,n);
				assert(used,"No Used\n");

				for(i=0;i<symWidth;i++){
					
					int sym = *symArray[i];

					// empty transitions
					// boardCell0UsedStageN=>N+1 OR NOT boardCell0IsSym0StageN OR boardCell0IsSym0StageN+1
					// and reverse
					varData *scv0 = getSymCellVar(varList,boardX,boardY,sym,n);
					assert(scv0,"No SCV0\n");
					varData *scv1 = getSymCellVar(varList,boardX,boardY,sym,n+1);
					assert(scv1,"No SCV1\n");					

					clause = createLinked(Malloc,Free);
					clauseVar = createClauseVar(used,0);
					addTailLinked(clause,clauseVar);
					clauseVar = createClauseVar(scv0,1);
					addTailLinked(clause,clauseVar);
					clauseVar = createClauseVar(scv1,0);
					addTailLinked(clause,clauseVar);

					assertBool(sizeLinked(clause) != 0,"Empty Clause Used");
					addTailLinked(clauseList,clause);

					clause = createLinked(Malloc,Free);
					clauseVar = createClauseVar(used,0);
					addTailLinked(clause,clauseVar);
					clauseVar = createClauseVar(scv1,1);
					addTailLinked(clause,clauseVar);
					clauseVar = createClauseVar(scv0,0);
					addTailLinked(clause,clauseVar);

					assertBool(sizeLinked(clause) != 0,"Empty Clause Used");
					addTailLinked(clauseList,clause);
				}
			}
		}
	}
}

int findGroup(void *param,void *data){

	treeNode *nodeParam = param;
	nameData *elabParam = nodeParam->data;
	int paramObj = elabParam->objId;
	int paramName = elabParam->nameId;

	optGroup *optData = data;
	int dataObj = optData->objId;
	int dataName = optData->nameId;

	if(dataObj == paramObj && dataName == paramName)
		return 0;
	return -1;
}

// Req and DesObj
// Opt and DesObj
void reqOptClausesInit(nodeType type,linkedList elabNodes,linkedList desObjNodes,indexList *varList,linkedList clauseList,linkedList optGroupList){

	int i;
	int elabSize = sizeLinked(elabNodes);
	treeNode **elabArray = toArrayLinked(elabNodes);		
	
	elabFullData elabTemp;
	elabFullData *elab = &elabTemp;

	for(i=0;i<elabSize;i++){

		treeNode *elabNode = elabArray[i];
		nameData *elabData = elabNode->data;

		int elabObj = elabData->objId;
		int elabName = elabData->nameId;
		setData *elabSet = elabData->set;

		if(optGroupList){
			optGroup *group = getLinked(optGroupList,findGroup,elabNode);
			if(!group){
				group = Malloc(sizeof(optGroup));
				group->nameId = elabName;
				group->objId = elabObj;
				group->list = createLinked(Malloc,Free);
				addTailLinked(optGroupList,group);
			}
			elabData->elabNum = sizeLinked(group->list);
			addTailLinked(group->list,elabNode);
		}
		
		elab->type = type;
		elab->elabId = elabName;
		elab->elabNum = elabData->elabNum;
		elab->objId = elabObj;
		elab->startData = elabSet;
		elab->endData = NULL;
		elab->stages = elabNode->stages;
		
		elabClauses(elab,desObjNodes,varList,clauseList);
	}
}

void reqOptClauses(rootData *rdata,indexList *varList,linkedList clauseList){

	// req
	reqOptClausesInit(reqType,rdata->reqNodes,rdata->desObjNodes,varList,clauseList,NULL);
	
	// opt
	linkedList optGroupList = createLinked(Malloc,Free);
	reqOptClausesInit(optType,rdata->optNodes,rdata->desObjNodes,varList,clauseList,optGroupList);
	
	// add that at least one of each opt group must be true
	int optGroupSize = sizeLinked(optGroupList);
	optGroup **optGroupArray = toArrayLinked(optGroupList);	
	
	// desObj
	linkedList desObjNodes = rdata->desObjNodes;
	int desObjSize = sizeLinked(desObjNodes);
	treeNode **desObjArray = toArrayLinked(desObjNodes);
	
	// at least one Opt-<Opt>-<Any Number>-DesObj-<DesObj>-Stage<Stage>
	int n,i,c,x;
	for(n=0;n<numStages;n++){
		
		for(x=0;x<optGroupSize;x++){

			optGroup *optGroup = optGroupArray[x];
			int optGroupObj = optGroup->objId;
			int optGroupName = optGroup->nameId;

			int optSize = sizeLinked(optGroup->list);
			treeNode **optArray = toArrayLinked(optGroup->list);

			for(c=0;c<desObjSize;c++){
			
				treeNode *desObjNode = desObjArray[c];
				nameData *desObjData = desObjNode->data;
			
				int desObjName = desObjData->nameId;
				int desObjObj = desObjData->objId;
			
				if(desObjObj != optGroupObj)
					continue;
				
				linkedList atLeastList = createLinked(Malloc,Free);
				for(i=0;i<optSize;i++){
					treeNode *optNode = optArray[i];

					// check if is valid at this stage
					nodeStages *stages = optNode->stages;
					if(n < stages->start || n > stages->end)
						continue;

					nameData *optData = optNode->data;
					int optNum = optData->elabNum;
					
					// if it was not created, it is not used and so is not needed in atLeastList
					varData *opt = getOptVar(varList,optGroupName,optNum,desObjName,n);
					if(!opt)
						continue;
				
					pushLinked(atLeastList,opt);
				}
				atLeastOne(atLeastList,clauseList);
				destroyLinked(atLeastList,NULL);
			}
		}
	}

	optGroup *rem;
	while((rem = popLinked(optGroupList))){
		destroyLinked(rem->list,NULL);
		Free(rem);
	}
	destroyLinked(optGroupList,NULL);
}

// this prints the clauses to be read by the CNF solver
void printClauses(FILE *file,indexList *varList,linkedList clauseList){

	int numVar = sizeVarList(varList);
	int numClause = sizeLinked(clauseList);
	fprintf(file,"p cnf %i %i\n",numVar,numClause);
	
	linkedList clause;
	while((clause = popLinked(clauseList))){
		
		clauseVarData *var;
		while((var = popLinked(clause))){

			varData *data = var->data;
			int printInt = data->value;
			if(var->negate)
				printInt = -printInt;
			fprintf(file,"%i ",printInt);
			Free(var);
		}

		fprintf(file,"0\n");
		destroyLinked(clause,NULL);
	}
}

int createSatOut(char *inFileStr,char *outFileStr,rootData *rdata,indexList *varList,linkedList fullTransNodes){

	FILE *inFile = fopen(inFileStr,"r");
	FILE *outFile = fopen(outFileStr,"w");
	char word[10];

	fscanf(inFile,"%s",word);
	if(strcmp(word,"UNSAT") == 0){
		fprintf(outFile,"UNSATISFIABLE");
		fclose(inFile);
		fclose(outFile);
		return -1;
	}
	if(strcmp(word,"SAT") != 0){
		printf("Error: Sat File Parsing Error.");
		exit(0);
	}
	
	indexList *outVars = createVarIndex();
	int ret;
	fscanf(inFile,"%i",&ret);

	while(ret != 0){
		
		// generally if not true, then not important
		// get varData of this variable in out sat
		varData *vdata = getVarByValue(varList,ret);
		
		fscanf(inFile,"%i",&ret);

		if(!vdata)
			continue;
			
		// only care about adding Trans, SymCell
		if(vdata->type == symCellVarType || vdata->type == transVarType)
			addSomeVar(outVars,vdata);
	}
	
	// trans array
	int transWidth = sizeLinked(fullTransNodes);
	tempTransVar **transArray = toArrayLinked(fullTransNodes);	
	
	treeNode *boardNode = rdata->boardNode;
	setData *bs = boardNode->data;
	
	int boardWidth = bs->width;
	int boardHeight = bs->height;
	cellData **boardSet = bs->setVars;
	
	// print board stage n
	// print transition n=>n+1
	// repeat
	int n,x,y,i,j;
	int spaceIter;
	int foundTrans = 1;

	for(n=0;n<numStages;n++){

		if(foundTrans){
			for(y=0;y<boardHeight;y++){
				for(x=0;x<boardWidth;x++){
					
					cellData *cell = boardSet[y*boardWidth+x];
					if(!cell)
						continue;

					int numSpace = cell->numSpaceBef;
					for(spaceIter=0;spaceIter<numSpace;spaceIter++)
						fprintf(outFile,".");
					if(numSpace)
						fprintf(outFile," ");

					linkedList symList = cell->symList;
					int symWidth = sizeLinked(symList);
					int **symArray = toArrayLinked(symList);
				
					for(i=0;i<symWidth;i++){
					
						//x, y, id, stage
						varData *vdata = getSymCellVar(outVars,x,y,*symArray[i],n);
						if(vdata){
							int *sc = vdata->data;
							char *symIdWord = getStringSym(sc[1]);
							fprintf(outFile,"%s ",symIdWord);
						}
					}
				}
				fprintf(outFile,"\n");
			}
			fprintf(outFile,"\n");
		}

		foundTrans = 0;
		for(j=0;j<transWidth;j++){
			tempTransVar *trans = transArray[j];
			int transId = trans->transId;
			int desObjId = trans->desObjId;

			// only need to check it exists
			varData *vdata = getTransVar(outVars,transId,desObjId,n);
			if(vdata){
				char *id = getStringSym(trans->transId);
				char *desObj = getStringSym(trans->desObjId);
				fprintf(outFile,"%s %s\n",id,desObj);
				foundTrans = 1;
			}
		}

		if(foundTrans)
			fprintf(outFile,"\n");
	}

	fclose(inFile);
	fclose(outFile);
	destroyVarIndex(outVars);	
	return 0;
}

char *combineStr(char *str1,char *str2){

	int len = strlen(str1) + strlen(str2) + 1;	
	char *both = Malloc(sizeof(char)*len);
	sprintf(both,"%s%s",str1,str2);
	return both;
}

void execute(treeNode *root){

	rootData *rdata = root->data;
	compilerDebug(rdata);
	postProc(rdata);
	
	linkedList fullTransNodes = expandTrans(rdata);
	indexList *varList = createVarList(rdata,fullTransNodes);

	linkedList clauseList = createLinked(Malloc,Free);
	startEndClauses(rdata,varList,clauseList);

	infraClauses(rdata,varList,clauseList,fullTransNodes,1,1);
	setUsedClauses(rdata,varList,clauseList,fullTransNodes);
	usedClauses(rdata,varList,clauseList,fullTransNodes);

	transClauses(rdata,varList,clauseList);
	reqOptClauses(rdata,varList,clauseList);

	if(flag == FLAG_DEBUG){
		FILE *dfile = fopen("debug.txt","w");
		printDebugClauses(dfile,varList,clauseList);
		fclose(dfile);
	}

	if(flag == FLAG_CNF || flag == FLAG_RUN){
		FILE *ofile = fopen("cnf.txt","w");
		printClauses(ofile,varList,clauseList);
		fclose(ofile);
	}
	
	if(flag == FLAG_RUN){
		// system
		char *cmd = combineStr(sabrDir,"cnfsat cnf.txt vars.txt");
		system(cmd);
		Free(cmd);
	}	

	if(flag == FLAG_RESULT || flag == FLAG_RUN){
		// read in from dimout.out
		// convert output from minisat to human readable
		createSatOut("vars.txt","result.txt",rdata,varList,fullTransNodes);
	}
	
	Free(sabrDir);
	freeArch(root);
	
	destroyLinked(fullTransNodes,singleFree);
	destroyLinked(clauseList,singleFree);
	destroyVarIndex(varList);
}
