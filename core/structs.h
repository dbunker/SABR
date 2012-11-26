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

// this file contains the searching function structures produced from AST

#ifndef STRUCTS_H
#define STRUCTS_H

#include "../utils/linkedlist.h"
#include "arch.h"
#include "var.h"

typedef struct {
	int nameId;
	int objId;

	// contains linked lists of nameData of this group
	linkedList list;
} optGroup;

// used in lex symbol table to connect value to string
typedef struct {
	int value;
	char *str;
} stringData;

typedef struct {		// clause vars make up a clause
	int negate;
	varData *data;
} clauseVarData;

typedef struct {
	int symId;
	int cellX;
	int cellY;
} tempSym;

typedef struct {
	int transId;
	setData *startData;
	setData *endData;

	int objId;
	int desObjId;		// every object description must mave an associated transition varible
	setData *desObjSet;
	nodeStages *stages;
	int isSim;

} tempTransVar;

void singleFree(void *data);
int intSearch(void *param,void *data);

void simplePrint(void *data);
int simpleComp(void *param,void *data);
int simpleSearch(void *param,void *data);

int findString(void *param,void *data);
// int findValue(void *param,void *data);
char *getStringSym(int value);

int findTemp(void *param,void *data);
int findSym(void *param,void *data);
int getBoardXY(setData *board,setData *desObj,int objX,int objY,int *retX,int *retY);

#endif
