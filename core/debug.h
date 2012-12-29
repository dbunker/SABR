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

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include "var.h"
#include "../utils/gendebug.h"
#include "../utils/linkedlist.h"

int printVar(void *data);
void printVarData(FILE *file,varData *vd);
void printDebugClause(FILE *fileName,linkedList clause);
void printDebugClausesVars(char *debugFileName,indexList *varList,linkedList clauseList);
void printDebugClauses(char *fileName,indexList *varList,linkedList clauseList);
void compilerDebug(rootData *rdata);
void postProc(rootData *rdata);
void freeArch(treeNode *rootNode);

#endif
