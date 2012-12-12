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

// this file deals with the tempvars and symbols in cells

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

// at least one of this list of varData
void atLeastOne(linkedList newVarList,linkedList clauseList){

	linkedList clause;
	clauseVarData *clauseVar;
	int i;

	int varSize = sizeLinked(newVarList);
	if(varSize < 1)
		return;

	varData **newVarArray = toArrayLinked(newVarList);
	
	// at least one
	clause = createLinked(Malloc,Free);
	for(i=0;i<varSize;i++){
		varData *var = newVarArray[i];
		clauseVar = createClauseVar(var,0);
		assert(clauseVar->data,"Least");
		addTailLinked(clause,clauseVar);
	}
	assertBool(sizeLinked(clause) != 0,"Empty Clause At Least One");
	addClause(clauseList,clause);
}

// at most one of this list of varData
void atMostOne(linkedList newVarList,linkedList clauseList){

	linkedList clause;
	clauseVarData *clauseVar;
	int i,c;

	int varSize = sizeLinked(newVarList);
	if(varSize < 1)
		return;

	varData **newVarArray = toArrayLinked(newVarList);
	
	// at most one
	for(i=0;i<varSize;i++){
		varData *var1 = newVarArray[i];

		for(c=i+1;c<varSize;c++){						
			varData *var2 = newVarArray[c];
			
			clause = createLinked(Malloc,Free);
			clauseVar = createClauseVar(var1,1);
			assert(clauseVar->data,"Most");
			addTailLinked(clause,clauseVar);
			clauseVar = createClauseVar(var2,1);
			assert(clauseVar->data,"Most");
			addTailLinked(clause,clauseVar);

			assertBool(sizeLinked(clause) != 0,"Empty Clause At Most One");
			addClause(clauseList,clause);
		}
	}
}

// both are list of OR clause vars (include negation info)
// IF varListA THEN varListB
// NOT (varA1 OR varA2) OR (varB1 OR varB2)
int ifThen(linkedList varListA,linkedList varListB,linkedList clauseList){

	linkedList clause;
	clauseVarData *clauseVarA;
	clauseVarData *clauseVarB;
	int i,c;
	
	int varSizeA = sizeLinked(varListA);
	clauseVarData **varArrayA = toArrayLinked(varListA);

	int varSizeB = sizeLinked(varListB);
	clauseVarData **varArrayB = toArrayLinked(varListB);

	if(varSizeA == 0 || varSizeB == 0)
		return -1;

	for(i=0;i<varSizeA;i++){

		clauseVarA = varArrayA[i];
		clauseVarA->negate = !(clauseVarA->negate);

		clause = createLinked(Malloc,Free);
		assert(clauseVarA->data,"If Then A");
		clauseVarA = createClauseVar(clauseVarA->data,clauseVarA->negate);
		addTailLinked(clause,clauseVarA);

		for(c=0;c<varSizeB;c++){
			
			clauseVarB = varArrayB[c];
			clauseVarB = createClauseVar(clauseVarB->data,clauseVarB->negate);
			assert(clauseVarB->data,"If Then B");
			addTailLinked(clause,clauseVarB);
		}
		assertBool(sizeLinked(clause) != 0,"Empty Clause If Then");
		addClause(clauseList,clause);
	}
	return 0;
}

// this will handle an individual cell of an elab-desobj pair
void handleCell(linkedList symList,indexList *varList,linkedList clauseList,elemInfo *elem){

	clauseVarData *clauseVar;
	int x,c;
	
	linkedList myTempList = elem->myTempList;
	int myTempSize = sizeLinked(myTempList);
	tempElem **myTempArray = toArrayLinked(myTempList);

	linkedList mySymList = elem->mySymList;
	int mySymSize = 0;
	symElem **mySymArray = NULL;

	if(mySymList){
		mySymSize = sizeLinked(mySymList);
		mySymArray = toArrayLinked(mySymList);
	}

	linkedList myCellLinked = elem->myCellLinked;
	int **myCellArray = toArrayLinked(myCellLinked);

	int myStage = elem->myStage;
	int desElabId = elem->desElabId;
	int desElabNum = 0;
	int desObjId = elem->desObjId;
	int desObjPlace = elem->desObjPlace;
	int elemIsNextStage = elem->isNextStage;
	
	// symbol array
	int symWidth = sizeLinked(symList);
	int **symArray = toArrayLinked(symList);
	
	// this is the main OR clause for the elements that could be in the cell (will only be SymCellVars)
	linkedList elemSymList = createLinked(Malloc,Free);

	// symbol options
	for(x=0;x<mySymSize;x++){
		
		symElem *sym = mySymArray[x];
		int symId = sym->symId;
		int isNeg = sym->isNeg;
		
		// add single option to be this symbol for this cell
		int cellName = *myCellArray[0];
		
		varData *var = getSymCellVarByName(varList,cellName,symId,myStage + elemIsNextStage);
		assert(var->data,"Wrong Handle Sym");
		clauseVar = createClauseVar(var,isNeg);
		addTailLinked(elemSymList,clauseVar);
	}

	// tempvar options
	if(myTempSize > 0){

		for(c=0;c<symWidth;c++){

			int symId = *symArray[c];
			int cellName = *myCellArray[0];
			varData *var = getSymCellVarByName(varList,cellName,symId,myStage + elemIsNextStage);

			linkedList negTempList = createLinked(Malloc,Free);
			linkedList posTempList = createLinked(Malloc,Free);

			for(x=0;x<myTempSize;x++){

				tempElem *temp = myTempArray[x];
				int isNeg = temp->isNeg;
				int tempCellName = temp->cellName;
				int tempIsNextStage = temp->isNextStage;

				varData *tempVar = getSymCellVarByName(varList,tempCellName,symId,myStage + tempIsNextStage);

				assert(tempVar->data,"Wrong Handle Temp");
				clauseVar = createClauseVar(tempVar,0);

				if(isNeg)	addTailLinked(negTempList,clauseVar);
				else		addTailLinked(posTempList,clauseVar);
			}

			int bothPosAndNeg = (sizeLinked(negTempList) > 0 && sizeLinked(posTempList) > 0);
			varData *negVar = NULL;

			if(bothPosAndNeg){
				negVar = getNegateVar(varList,desElabId,desElabNum,desObjId,desObjPlace,myStage,0);
				if(!negVar)
					negVar = createNegateVar(varList,desElabId,desElabNum,desObjId,desObjPlace,myStage,0);
			}

			// this will be: IF ( <Cell for tempvar is symbol> ) THEN 
			// ( <Cell for connected var is symbol> OR <Other symbol in parrens> OR Negated )
			if(sizeLinked(posTempList) > 0){
				
				if(bothPosAndNeg){
					assert(negVar,"Var Is Null Pos 0");
					clauseVar = createClauseVar(negVar,0);
					pushLinked(elemSymList,clauseVar);
				}

				assert(var,"Var Is Null Pos 1");
				clauseVar = createClauseVar(var,0);

				pushLinked(elemSymList,clauseVar);
				ifThen(posTempList,elemSymList,clauseList);
				popLinked(elemSymList);
				Free(clauseVar);
				
				if(bothPosAndNeg){
					clauseVar = popLinked(elemSymList);
					Free(clauseVar);
				}
			}	

			// this will be: IF ( <Cell for tempvar is symbol> ) THEN 
			// ( <Cell for connected var is symbol> OR <Other cell in parrens> OR Not-Negated )
			if(sizeLinked(negTempList) > 0){
				
				if(bothPosAndNeg){
					assert(negVar,"Var Is Null Neg 0");
					clauseVar = createClauseVar(negVar,1);
					pushLinked(elemSymList,clauseVar);
				}

				assert(var,"Var Is Null Neg 1");
				clauseVar = createClauseVar(var,1);

				pushLinked(elemSymList,clauseVar);
				ifThen(negTempList,elemSymList,clauseList);
				popLinked(elemSymList);
				Free(clauseVar);

				if(bothPosAndNeg){
					clauseVar = popLinked(elemSymList);
					Free(clauseVar);
				}
			}

			destroyLinked(posTempList,singleFree);
			destroyLinked(negTempList,singleFree);
		}
		destroyLinked(elemSymList,singleFree);
	}

	// equivalent to if true then elemSymList
	else{
		if(sizeLinked(elemSymList) > 0){
			assertBool(sizeLinked(elemSymList),"Empty Clause Blank Handle");
			addClause(clauseList,elemSymList);
		}
	}
}

// elem to be used in handleCell
void addElemVar(elemInfo *elem,linkedList symList,linkedList tempList,int id,int isNeg){

	// if it is a symbol, just add to associated symbol list
	int *isSym = getLinked(symList,findSym,&id);
	if(isSym){

		symElem *sym = Malloc(sizeof(symElem));
		sym->isNeg = isNeg;
		sym->symId = id;
		addTailLinked(elem->mySymList,sym);
	}
	else{
		int tempId = id;
		tempElem *foundTemp = getLinked(tempList,findTemp,&tempId);
		
		// foundTemp is NULL if a temporary variable only occurs in (...), so there are no board values to represent it
		// this should be caught by compilerDebug
		assert(foundTemp,"Temporary variable does not exist");

		tempElem *newTemp = Malloc(sizeof(tempElem));
		newTemp->isNextStage = foundTemp->isNextStage;
		newTemp->tempId	= foundTemp->tempId;
		newTemp->cellName = foundTemp->cellName;
		newTemp->isNeg = isNeg;
		addTailLinked(elem->myTempList,newTemp);		
	}
}

// for initial processing
void addTempVar(linkedList tempList,int id,int isNextStage,linkedList symList,linkedList brackVars,indexList *varList){

	// if their is no temp, return
	if(!id) return;

	int *cellP = peekLinked(brackVars);
	int cell = *cellP;

	// if it is a symbol, it is not a tempVar
	int *isSym = getLinked(symList,findSym,&id);
	if(!isSym){

		int tempId = id;
		tempElem *foundTemp = getLinked(tempList,findTemp,&tempId);
		
		// if temp already exists, we don't need to re-add it
		if(foundTemp)
			return;

		// need to create a new temp
		tempElem *newTemp = Malloc(sizeof(tempElem));
		newTemp->isNextStage = isNextStage;
		newTemp->tempId = id;
				
		newTemp->cellName = cell;
		addTailLinked(tempList,newTemp);
	}
}

void *intCopy(void *data){
	int *d = data;
	int *new = Malloc(sizeof(int));
	*new = *d;
	return new;
}

// this produces the output for this specific elab (trans,transsim,req,opt) and desobj
void elabClauses(elabFullData *elab,linkedList desObjNodes,indexList *varList,linkedList clauseList){

	int c,x,y,r,n;
	linkedList clause;
	clauseVarData *clauseVar;

	// desObj
	int desObjWidth = sizeLinked(desObjNodes);
	treeNode **desObjArray = toArrayLinked(desObjNodes);
	
	nodeType type = elab->type;
	int elabObj = elab->objId;
	int elabName = elab->elabId;

	int elabNum = elab->elabNum;
	setData *elabStartSet = elab->startData;
	setData *elabEndSet = elab->endData;
	
	int height = elabStartSet->height;
	int width = elabStartSet->width;
	elabData **setVars;
	int isNextStage;
	
	for(c=0;c<desObjWidth;c++){
		
		treeNode *desObjNode = desObjArray[c];
		nameData *desObjData = desObjNode->data;
		
		int desObjName = desObjData->nameId;
		int desObjObj = desObjData->objId;
		if(desObjObj != elabObj)
			continue;
		
		setData *desObjSet = desObjData->set;
		manyData **many = desObjSet->setVars;
		int manyWidth = desObjSet->width;
		
		// for temporary variables as they are observed
		linkedList tempList = createLinked(Malloc,Free);
		
		// if this is a trans, it will go through twice to get all temp vars
		// first from start, then from end
		isNextStage = 0;
		setVars = elabStartSet->setVars;
		while(setVars){
			for(y=0;y<height;y++){
				for(x=0;x<width;x++){
		
					elabData *elab = setVars[y*width+x];
					if(!elab || elab->isAny) 
						continue;
					
					manyData *manyThis = many[manyWidth*y+x];
					linkedList brackVars = manyThis->brackVars;
					linkedList symList = manyThis->symList;

					// if it is a symbol, it is ignored at this stage
					int tempVarName = elab->tempVarName;
					addTempVar(tempList,tempVarName,isNextStage,symList,brackVars,varList);
				}
			}
			
			setVars = NULL;
			if(elabEndSet && isNextStage == 0){
				setVars = elabEndSet->setVars;
			}
			isNextStage = 1;
		}		

		// create an elem for each cell of the elab specification
		linkedList elemList = createLinked(Malloc,Free);

		isNextStage = 0;
		setVars = elabStartSet->setVars;
		while(setVars){
			for(y=0;y<height;y++){
				for(x=0;x<width;x++){
	
					elabData *elabTemp = setVars[y*width+x];
					if(!elabTemp || elabTemp->isAny)
						continue;
					
					assertBool((manyWidth == width),"Width Mismatch");
					manyData *manyThis = many[y*width+x];
					linkedList brackVars = manyThis->brackVars;
					
					int tempVarName = elabTemp->tempVarName;
					linkedList negVars = elabTemp->negVars;
					linkedList posVars = elabTemp->posVars;

					int *boardCellP = peekLinked(brackVars);
					int boardCell = *boardCellP;
					linkedList symList = manyThis->symList;
					assert(symList,"Cell Elab SymList 1");

					// if there is a connection between cells (equality), it is better to
					// apply constraints to as few cells as possible, so use the tempCell, 
					// rather than the current cell
					linkedList connectTempCell = NULL;				

					// add an elab to connect this tempVar, if needed (if the tempVar 
					// is not represented by tempElem) this will be added as another elem
					if(tempVarName){

						int *isSym = getLinked(symList,findSym,&tempVarName);
						if(isSym){
							// only need to add it once if it is a symbol
							if(sizeLinked(posVars) == 0){
								int *tvn = Malloc(sizeof(int));
								*tvn = tempVarName;
								addTailLinked(posVars,tvn);
							}
						}
						
						else{
							// cant be in symlist
							elemInfo *elem = Malloc(sizeof(elemInfo));
							elem->myTempList = createLinked(Malloc,Free);
							elem->mySymList = NULL;
							elem->desElabId = elabName;
							elem->isNextStage = isNextStage;
							elem->desObjId = desObjName;
							elem->desObjPlace = y*width+x;
							elem->cellSymList = symList;
							elem->myCellLinked = copyLinked(brackVars,Malloc,Free,intCopy);

							// add var
							addElemVar(elem,symList,tempList,tempVarName,0);
							
							// want to now link all information to the original tempVar cell
							tempElem *foundTemp = peekLinked(elem->myTempList);
							int tempCell = foundTemp->cellName;
							int tempStage = foundTemp->isNextStage;
	
							// if it is not the orignal tempVar, a connection is needed, 
							// otherwise it is not
							if(tempCell != boardCell || tempStage != isNextStage){

								// add elem to list
								addTailLinked(elemList,elem);
	
								int *newTempCell = Malloc(sizeof(int));
								*newTempCell = tempCell;

								connectTempCell = createLinked(Malloc,Free);
								addTailLinked(connectTempCell,newTempCell);
							}
							else{
								destroyLinked(elem->myCellLinked,singleFree);
								destroyLinked(elem->myTempList,singleFree);
								Free(elem);
							}
						}
					}

					int negVarSize = sizeLinked(negVars);
					int posVarSize = sizeLinked(posVars);
	
					// add elab for info in parens
					if(negVarSize > 0 || posVarSize > 0){
						
						int **negVarArray = toArrayLinked(negVars);
						int **posVarArray = toArrayLinked(posVars);
						
						// these are what will be specified to
						elemInfo *elem = Malloc(sizeof(elemInfo));
						elem->myTempList = createLinked(Malloc,Free);
						elem->mySymList = createLinked(Malloc,Free);
						elem->desElabId = elabName;
						elem->isNextStage = isNextStage;
						elem->desObjId = desObjName;
						elem->desObjPlace = y*width+x;
						elem->cellSymList = symList;

						if(connectTempCell)
							elem->myCellLinked = copyLinked(connectTempCell,Malloc,Free,intCopy);
						else
							elem->myCellLinked = copyLinked(brackVars,Malloc,Free,intCopy);

						for(r=0;r<posVarSize;r++){
							int id = *posVarArray[r];
							addElemVar(elem,symList,tempList,id,0);
						}
						for(r=0;r<negVarSize;r++){
							int id = *negVarArray[r];
							addElemVar(elem,symList,tempList,id,1);
						}
	
						addTailLinked(elemList,elem);
					}
					if(connectTempCell)
						destroyLinked(connectTempCell,singleFree);
				}
			}

			setVars = NULL;
			if(elabEndSet && isNextStage == 0){
				setVars = elabEndSet->setVars;
			}
			isNextStage = 1;
		}

		// free the list of temporary variables
		destroyLinked(tempList,singleFree);

		// handleCell creates clauses that will be refactored depending on the elab type
		linkedList preClauses = createLinked(Malloc,Free);
		elemInfo *elem;
		while((elem = popLinked(elemList))){
			// if it is the next stage, we can encode that by adding one to the stage

			// board cell sym list
			linkedList symList = elem->cellSymList;
			assert(symList,"Cell Elab SymList 3");

			if(type == transType){

				// only valid stages
				nodeStages *stages = elab->stages;
				int start = stages->start;
				int end = stages->end;

				for(n=start;n<end-1;n++){
					elem->myStage = n;
					handleCell(symList,varList,preClauses,elem);
					
					while((clause = popLinked(preClauses))){

						varData *trans = getTransVar(varList,elabName,desObjName,n);
						clauseVar = createClauseVar(trans,1);
						pushLinked(clause,clauseVar);

						addClause(clauseList,clause);
					}
				}
			}
			
			else if(type == reqType){

				// only valid stages
				nodeStages *stages = elab->stages;
				int start = stages->start;
				int end = stages->end;

				for(n=start;n<end;n++){
					elem->myStage = n;
					handleCell(symList,varList,preClauses,elem);
				
					while((clause = popLinked(preClauses))){
						addClause(clauseList,clause);
					}
				}
			}

			else if(type == optType){

				// only valid stages
				nodeStages *stages = elab->stages;
				int start = stages->start;
				int end = stages->end;

				for(n=start;n<end;n++){
					elem->myStage = n;
					handleCell(symList,varList,preClauses,elem);
				
					while((clause = popLinked(preClauses))){

						varData *opt = getOptVar(varList,elabName,elabNum,desObjName,n);
						if(!opt)
							opt = createOptVar(varList,elabName,elabNum,desObjName,n);
						
						clauseVar = createClauseVar(opt,1);
						pushLinked(clause,clauseVar);
						addClause(clauseList,clause);
					}
				}
			}

			else if(type == startType || type == endType){		

				if(type == startType)	elem->myStage = 0;
				else			elem->myStage = numStagesGlobal-1;

				handleCell(symList,varList,preClauses,elem);
				
				while((clause = popLinked(preClauses))){
					addClause(clauseList,clause);
				}
			}
			
			destroyLinked(elem->myCellLinked,singleFree);
			destroyLinked(elem->myTempList,singleFree);
			if(elem->mySymList)
				destroyLinked(elem->mySymList,singleFree);
			Free(elem);
		}
		destroyLinked(preClauses,NULL);
		destroyLinked(elemList,NULL);
	}
}

