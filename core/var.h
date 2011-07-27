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

// this file contains var info

#ifndef VAR_H
#define VAR_H

// for data space in varData->data not used
#define NOT_USED -1

#include "../utils/skiplist.h"

// symCellVarType is associated with a certain symbol-cell-stage being true
// transVarType is associated with a certain transition-description-stage being true
// transPartVarType is the potential boolean form of transVar (less clauses for at-most-one)
// usedVarType indicates a cell is used by some transform
// negateVarType if both positive and negatives are in () in elab (i.e. (!a,b)) this must be used
// optVarType indicates an opt was used
// unknownVarType use this if other information is known, but not the type, during lookup
typedef enum {	symCellVarType,transVarType,transPartVarType,usedVarType,
		negateVarType,optVarType,unknownVarType } varType;

typedef struct {
	// this is negative for changing 2 symbols to: symbol and not symbol
	// can have an inherent negation of the variable
	int value;
	
	int size;
	varType type;

	// is actual data for var (sequence of int*, size indicated above)
	int *data;
} varData;

typedef struct {
	int size;

	// also sequence of int*
	int *key;
	varData *vdat;
} varInd;

typedef struct {
	// contains varInd*
	skipList keyList;

	// contains varData*
	linkedList fullList;

	// since some variables are represented as negatives, 
	// the number of vars will be less than the size of fullList
	int numVar;
} indexList;

int printOutVar(void *param);
indexList *createVarIndex();
void destroyVarIndex(indexList *ind);
int sizeVarList(indexList *varList);
void addSomeVar(indexList *varList,varData *vdat);

varData *getVarByValue(indexList *varList,int val);

varData *createSymCellVar(indexList *varList,int symId,int cellName,int x,int y,int stage,varData *negOfVar);
varData *getSymCellVar(indexList *varList,int x,int y,int id,int stage);
varData *getSymCellVarByName(indexList *varList,int name,int id,int stage);

varData *createTransVar(indexList *varList,int id,int objId,int desObjId,int stage);
varData *getTransVar(indexList *varList,int id,int desObjId,int stage);

varData *getTransPartVar(indexList *varList,int partId,int stage);
varData *createTransPartVar(indexList *varList,int partId,int stage);

varData *getUsedVar(indexList *varList,int x,int y,int stage);
varData *createUsedVar(indexList *varList,int cellName,int x,int y,int stage);

varData *getNegateVar(indexList *varList,int desElab,int desElabNum,int desObj,int desObjPlace,int stageNum,int transFinal);
varData *createNegateVar(indexList *varList,int desElab,int desElabNum,int desObj,int desObjPlace,int stageNum,int transFinal);

varData *createOptVar(indexList *varList,int desElab,int desElabNum,int desObj,int stageNum);
varData *getOptVar(indexList *varList,int desElab,int desElabNum,int desObj,int stageNum);

#endif
