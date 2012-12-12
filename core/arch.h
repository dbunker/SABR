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

// this file stores AST structure information

#ifndef ARCH_H
#define ARCH_H

#include "../utils/linkedlist.h"

// for unnamed DesObj, Req, etc. name invention
int inventNameNumGlobal;

// indicates if the end of file has been reached
int endFileGlobal;

// the symbol table produced by lex
linkedList symTableGlobal;

// the user gives the number of stages they are willing to test up to
int numStagesGlobal;

// potential command line argument
#define FLAG_DEBUG 	1	// prog.tbl =compile=> debug.out
#define FLAG_CNF	2	// prog.tbl =compile=> dimin.in
#define FLAG_RUN 	3	// prog.tbl =compile=> dimin.in =cnf=> dimout.out =postproc=> result.out
#define FLAG_RESULT	4	// prog.tbl =compile=> =nothing=> dimout.out =postproc=> result.out
int flagGlobal;

// define files
#define CNF_EXEC			"cnfsat"
#define TEMP_CLAUSE_FILE	".temp-clauses.txt"
#define CNF_FILE			"cnf.txt"
#define OUT_VARS_FILE		"vars.txt"
#define RESULT_FILE			"result.txt"
#define DEBUG_CLAUSE_FILE	"debug.txt"

// line number
int curLineNumGlobal;

// directory
char *sabrDirGlobal;

// temporary file
FILE *tempClausesFileGlobal;

// clauses
int numClausesGlobal;

// global clauseList
linkedList clauseListGlobal;

// source file to read from for yacc
FILE *yyin;

// each corresponds to a node type
typedef enum { 	rootType, symType, boardType, startType, endType, transType, transSimType,
		tempSetType, objType, desObjType, reqType, optType,
		charType, manyType, elabType } nodeType;

// all nodes on the tree
// data is rootData (root), setData (board,start,end), nameData (obj,desobj,opt,req), or transData (trans,transsim)
// spaces is a linkedList of int* indicating number of . after each board cell
// stages is for elab (trans,req,opt) to indicate stages they are valid
typedef struct {
	nodeType type;
	void *data;
	void *spaces;
	void *stages;
} treeNode;

// when generating cells in linkedlist, an endline
// is represented by this (NULL cannot be stored in list)
#define ENDLINE ((void*)(-1))

typedef struct {
	linkedList symbols;
	int nameId;
} symListInfo;

// this is if an elab 
// exists for specific stages, not all stages
typedef struct {
	int start;
	int end;
} nodeStages;

// the one root node
typedef struct {
	// contains list of symListInfo
	linkedList symLists;
	
	treeNode *boardNode;
	treeNode *startNode;
	treeNode *endNode;

	// contain treeNodes
	linkedList objNodes;
	linkedList desObjNodes;
	linkedList transNodes;
	linkedList reqNodes;
	linkedList optNodes;

} rootData;

typedef struct {
	linkedList symList;
	int symListName;
	int cellName;

	// this is for determining placement of . in output
	int numSpaceBef;
} cellData;

typedef struct {
	// this is the stand alone portion (i.e. tempVarName:(negVars and posVars))
	int tempVarName;

	// this indicates it is any (?)
	int isAny;

	// contains int* which refer to values in the symlist in the
	// corresponding DesObj manyData (or perhaps a tempVar)
	// these lists can be set to NULL
	linkedList negVars;
	linkedList posVars;
} elabData;

typedef struct {
	// contains symList associated with this DesObj cell
	linkedList symList;
	
	// contains board cells names (int*)
	linkedList brackVars;
} manyData;

// this is the 2 dimensional set indexed by [y*width + x]
// this is the only part of sym, board, start, end
// for extra values, these are 0s at end of each line
// type can be:
// charType  setVars is (int**) the single variable
// manyType  setVars is (manyData**) the list of variables in the brackets
// elabType  setVars is (elabData**) list of negative and positive variables in parens
//				     and name of temporary variable
// boardType setVars is (cellData**) list of board cells or obj cells and their associated symlist by name
typedef struct {
	int height;
	int width;
	void *setVars;
} setData;

// obj desObj req desReq have more info than just the set
typedef struct {
	int nameId;
	int objId;

	// used if it is an opt and so part of an opt group
	int elabNum;
	setData *set;
} nameData;

// as the set is being built it is stored in here
// set contains int* of text found
typedef struct {
	int numLines;
	int maxWidth;
	int curWidth;
	linkedList set;
} startSetData;

// transform
typedef struct {
	int transId;
	int objId;
	setData *startData;
	setData *endData;
} transData;

int initSym();
int addSymbol(char*);
void yyerror(char*);
void endError();
void *Malloc(size_t);
void Free(void*);
void execute(treeNode*);

treeNode *symNode(treeNode *newSymList,treeNode *symLists);
treeNode *statementNodes(treeNode *symbols,treeNode *board,treeNode *start,treeNode *end,treeNode *root);
treeNode *setStages(int varId1,int varId2);
treeNode *choiceNode(int tok,treeNode *choice,treeNode *root);
treeNode *storeNode(int tok,treeNode *set);
treeNode *nameNode(int tok,treeNode *stagesNode,int nameId,int objId,treeNode *set);
treeNode *transNode(int type,treeNode *stagesNode,int transId,int objId,treeNode *startSet,treeNode *endSet);
treeNode *setNode(int tok,treeNode *var,treeNode *set);
treeNode *setCommaNode(int tok,int varId,treeNode *varList);
treeNode *setVarNode(int tok,int varId,treeNode *varList);
treeNode *setBoardVarNode(int tok,int varId,int sym);

#endif
