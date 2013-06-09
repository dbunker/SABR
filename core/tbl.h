// this file contains relevent compiler info

#ifndef TBL_H
#define TBL_H

#include "structs.h"

clauseVarData *createClauseVar(varData *var,int neg);
int addClause(linkedList,linkedList);
void deleteFile(char*);

#endif
