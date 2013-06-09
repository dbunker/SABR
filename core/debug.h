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
