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

// this file contains variable uttilities

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
#include "../utils/skiplist.h"
#include "../utils/gendebug.h"

int compValueVar(void*,void*);
int compGenVar(void*,void*);

/***************** Control *************/

indexList *createVarIndex(){

	indexList *retList = Malloc(sizeof(indexList));
	retList->keyList = createSkip(Malloc,Free,compGenVar);
	retList->fullList = createLinked(Malloc,Free);
	retList->numVar = 0;
	return retList;
}

void delSkip(void *data){

	varInd *vi = data;
	Free(vi->key);
	Free(vi);
}

void delLink(void *data){
	
	varData *vd = data;
	Free(vd->data);
	Free(vd);
}

void destroyVarIndex(indexList *ind){
	
	destroySkip(ind->keyList,delSkip);
	destroyLinked(ind->fullList,delLink);
	Free(ind);
}

int sizeVarList(indexList *varList){
	indexList *retList = varList;
	return retList->numVar;
}

/***************** GenVar *************/

int compGenVar(void *first,void *second){

	varInd *pdat = first;
	varInd *ldat = second;

	int *paramData = pdat->key;
	int *listData = ldat->key;
	int psize = pdat->size;
	int lsize = ldat->size;
	int n;

	// first sort by size
	if(lsize < psize)
		return -1;
	if(lsize > psize)
		return 1;

	// then sort by internals
	for(n=0;n<psize;n++){

		if(listData[n] < paramData[n])
			return -1;
		if(listData[n] > paramData[n])
			return 1;
	}

	return 0;
}

varData *getGenVar(indexList *varList,varType type,int *vals,int size){

	indexList *indList = varList;
	skipList *sList = indList->keyList;

	varInd ind;
	ind.key = vals;
	ind.size = size;

	varInd *retInd = getSkip(sList,&ind);
	if(!retInd)
		return NULL;

	varData *retData = retInd->vdat;
	return retData;
}

// for vardata indexes
void createGenInd(indexList *varList,varData *vdat,int *vals,int size){
	indexList *indList = varList;

	int *var = Malloc(sizeof(int)*size);
	int n;
	
	for(n=0;n<size;n++)
		var[n] = vals[n];

	varInd *vind = Malloc(sizeof(varInd));
	vind->size = size;
	vind->key = var;
	vind->vdat = vdat;
	
	skipList sList = indList->keyList;
	insertSkip(sList,vind);
}

// add to general linkedlist and as a value
varData *createGenVarSet(indexList *varList,varType type,int *vals,int size,int value){
	indexList *indList = varList;
	linkedList fullList = indList->fullList;

	int *var = Malloc(sizeof(int)*size);
	int n;
	
	for(n=0;n<size;n++)
		var[n] = vals[n];
	
	varData *vdat = Malloc(sizeof(varData));
	if(!value){
		vdat->value = indList->numVar + 1;
		indList->numVar++;
	}
	else{
		vdat->value = value;
	}

	vdat->type = type;
	vdat->data = var;
	vdat->size = size;

	// add as value
	int valsForVal[] = {unknownVarType,vdat->value};
	createGenInd(varList,vdat,valsForVal,2);
	
	pushLinked(fullList,vdat);
	return vdat;
}

varData *createGenVar(indexList *varList,varType type,int *vals,int size){
	return createGenVarSet(varList,type,vals,size,0);
}

void addSomeVar(indexList *varList,varData *vdat){

	int *data = vdat->data;

	if(data[0] == symCellVarType)
		createSymCellVar(varList,data[1],data[2],data[3],data[4],data[5],0);
	else if(data[0] == transVarType)
		createTransVar(varList,data[1],0,data[2],data[3]);
}

/***************** Var *************/

varData *getVarByValue(indexList *varList,int val){

	int vals[] = {unknownVarType,val};
	varData *vdat = getGenVar(varList,unknownVarType,vals,2);
	return vdat;
}

/***************** SymCellVar *************/

varData *getSymCellVar(indexList *varList,int x,int y,int symId,int stage){

	int vals[] = {symCellVarType,symId,NOT_USED,x,y,stage};
	varData *vdat = getGenVar(varList,symCellVarType,vals,6);
	return vdat;
}

varData *getSymCellVarByName(indexList *varList,int cellName,int symId,int stage){

	int vals[] = {symCellVarType,symId,cellName,NOT_USED,NOT_USED,stage};
	varData *vdat = getGenVar(varList,symCellVarType,vals,6);
	return vdat;
}

// a symbol can be set to be inherently negative
varData *createSymCellVar(indexList *varList,int symId,int cellName,int x,int y,int stage,varData *negOfVar){

	int value = 0;
	if(negOfVar)
		value = -(negOfVar->value);
	
	int vals0[] = {symCellVarType,symId,cellName,x,y,stage};
	varData *vdat = createGenVarSet(varList,symCellVarType,vals0,6,value);

	int vals1[] = {symCellVarType,symId,NOT_USED,x,y,stage};
	createGenInd(varList,vdat,vals1,6);
	
	int vals2[] = {symCellVarType,symId,cellName,NOT_USED,NOT_USED,stage};
	createGenInd(varList,vdat,vals2,6);
	
	return vdat;
}

void printSymCellVar(FILE *file,int *sv){
	fprintf(file,"%sIs%sStage%i",
		getStringSym(sv[2]),getStringSym(sv[1]),sv[5]);
}

/***************** TransVar *************/

varData *getTransVar(indexList *varList,int id,int desObjId,int stage){

	int vals[] = {transVarType,id,desObjId,stage};
	varData *vdat = getGenVar(varList,transVarType,vals,4);
	return vdat;
}

varData *createTransVar(indexList *varList,int id,int objId,int desObjId,int stage){

	int vals[] = {transVarType,id,desObjId,stage};
	varData *vdat = createGenVar(varList,transVarType,vals,4);

	createGenInd(varList,vdat,vals,4);
	return vdat;
}

void printTransVar(FILE *file,int *td){

	fprintf(file,"Trans-%s-%s-Stage%i=>%i",
		getStringSym(td[1]),getStringSym(td[2]),td[3],td[3]+1);
}

/***************** TransPartVar *************/

varData *getTransPartVar(indexList *varList,int partId,int stage){

	int vals[] = {transPartVarType,partId,stage};
	varData *vdat = getGenVar(varList,transPartVarType,vals,3);
	return vdat;
}

varData *createTransPartVar(indexList *varList,int partId,int stage){

	int vals[] = {transPartVarType,partId,stage};
	varData *vdat = createGenVar(varList,transPartVarType,vals,3);

	createGenInd(varList,vdat,vals,3);
	return vdat;
}

void printTransPartVar(FILE *file,int *td){

	fprintf(file,"TransPart-%i-Stage%i=>%i",
		td[1],td[2],td[2]+1);
}

/***************** UsedVar *************/

varData *getUsedVar(indexList *varList,int x,int y,int stage){

	int vals[] = {usedVarType,NOT_USED,x,y,stage};
	varData *vdat = getGenVar(varList,usedVarType,vals,5);
	return vdat;
}

varData *createUsedVar(indexList *varList,int cellName,int x,int y,int stage){

	int vals0[] = {usedVarType,cellName,x,y,stage};
	varData *vdat = createGenVar(varList,usedVarType,vals0,5);

	int vals1[] = {usedVarType,NOT_USED,x,y,stage};
	createGenInd(varList,vdat,vals1,5);
	return vdat;
}

void printUsedVar(FILE *file,int *uv){
	fprintf(file,"%sUsedStage%i=>%i",
		getStringSym(uv[1]),uv[4],uv[4]+1);
}

/***************** NegateVar *************/

varData *getNegateVar(indexList *varList,int desElab,int desElabNum,int desObj,int desObjPlace,int stageNum,int transFinal){

	int vals[] = {negateVarType,desElab,desElabNum,desObj,desObjPlace,stageNum,transFinal};
	varData *vdat = getGenVar(varList,negateVarType,vals,7);
	return vdat;
}

varData *createNegateVar(indexList *varList,int desElab,int desElabNum,int desObj,int desObjPlace,int stageNum,int transFinal){

	int vals[] = {negateVarType,desElab,desElabNum,desObj,desObjPlace,stageNum,transFinal};
	varData *vdat = createGenVar(varList,negateVarType,vals,7);
	createGenInd(varList,vdat,vals,7);
	return vdat;
}

void printNegateVar(FILE *file,int *nv){
	fprintf(file,"Negate-%s-%i-%s-%i-Stage-%i-%i",
		getStringSym(nv[1]),nv[2],getStringSym(nv[3]),nv[4],nv[5],nv[6]);
}

/***************** OptVar *************/
// Opt-(desElab)-(desElabNum)-DesObj-(desObj)-Stage(stageNum)

varData *getOptVar(indexList *varList,int desElab,int desElabNum,int desObj,int stageNum){

	int vals[] = {optVarType,desElab,desElabNum,desObj,stageNum};
	varData *vdat = getGenVar(varList,optVarType,vals,5);
	return vdat;
}

varData *createOptVar(indexList *varList,int desElab,int desElabNum,int desObj,int stageNum){
	
	int vals[] = {optVarType,desElab,desElabNum,desObj,stageNum};
	varData *vdat = createGenVar(varList,optVarType,vals,5);
	createGenInd(varList,vdat,vals,5);
	return vdat;
}

void printOptVar(FILE *file,int *ov){
	fprintf(file,"Opt-%s-%i-DesObj-%s-Stage%i",
		getStringSym(ov[1]),ov[2],getStringSym(ov[3]),ov[4]);
}

/***************** Printer *************/

void printVarData(FILE *file,varData *vd){

	if	(vd->type == symCellVarType)		printSymCellVar(file,vd->data);
	else if	(vd->type == transVarType)		printTransVar(file,vd->data);
	else if	(vd->type == transPartVarType)		printTransPartVar(file,vd->data);
	else if	(vd->type == usedVarType)		printUsedVar(file,vd->data);
	else if	(vd->type == negateVarType)		printNegateVar(file,vd->data);
	else if	(vd->type == optVarType)		printOptVar(file,vd->data);
	else						{ assert(NULL,"No Type"); }
	
	// print sat value for reference
	fprintf(file,"(%i)",vd->value);
}
