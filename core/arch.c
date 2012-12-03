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

// this file handles the building of the AST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tbl.h"
#include "structs.h"
#include "arch.h"
#include "debug.h"
#include "../parser/y.tab.h"
#include "../utils/linkedlist.h"
#include "../utils/gendebug.h"

void yyparse();

treeNode *makeRoot(){

	treeNode *root = Malloc(sizeof(treeNode));
	rootData *data = Malloc(sizeof(rootData));
	data->objNodes = createLinked(Malloc,Free);
	data->desObjNodes = createLinked(Malloc,Free);
	data->transNodes = createLinked(Malloc,Free);
	data->reqNodes = createLinked(Malloc,Free);
	data->optNodes = createLinked(Malloc,Free);
	root->type = rootType;
	root->data = data;
	return root;
}

treeNode *statementNodes(treeNode *symbols,treeNode *board,treeNode *start,treeNode *end,treeNode *root){

	if(!root)
		root = makeRoot();

	rootData *data = root->data;
	data->symLists = symbols->data;
	data->boardNode = board;
	data->startNode = start;
	data->endNode = end;

	Free(symbols);
	return root;
}

int inventName(char *name){

	char str[30];
	sprintf(str,"+%s%i+",name,inventNameNum);
	inventNameNum++;
	return addSymbol(str);
}

// create root at end of chain then build it up
treeNode *choiceNode(int tok,treeNode *choice,treeNode *root){

	if(!root)
		root = makeRoot();
	rootData *data = root->data;
	
	if(tok == TRANSFORM || tok == REQUIRE || tok == OPTION){

		if(!choice->stages){
			nodeStages *stages = Malloc(sizeof(nodeStages));
			stages->start = 0;
			stages->end = numStages;
			choice->stages = stages;
		}
	}
	
	switch(tok){
		case TRANSFORM: 	pushLinked(data->transNodes,choice);	break;
		case OBJECT: 		pushLinked(data->objNodes,choice); 		break;
		case DESOBJECT: 	pushLinked(data->desObjNodes,choice); 	break;
		case REQUIRE: 		pushLinked(data->reqNodes,choice); 		break;
		case OPTION: 		pushLinked(data->optNodes,choice); 		break;
		default:			assert(NULL,"Node Error");
	}
	return root;
}

treeNode *setStages(int varId1,int varId2){

	char *var1 = getStringSym(varId1);
	char *var2 = getStringSym(varId2);

	int v1 = atoi(var1);
	int v2 = atoi(var2);

	nodeStages *stages = Malloc(sizeof(nodeStages));
	stages->start = v1;
	stages->end = v2;

	treeNode *node = Malloc(sizeof(treeNode));
	node->data = stages;
	return node;
}

setData *createSet(startSetData *notParsed){

	linkedList list = notParsed->set;
	int height = notParsed->numLines;
	int width = notParsed->maxWidth;
	
	void **set = Malloc(sizeof(void*)*height*width);
	int x = 0;
	int y = 0;
	
	int i;
	for(i=0;i<width*height;i++)
		set[i] = NULL;

	void *var = popLinked(list);
	while(var) {
		if(var == ENDLINE){
			x=0;
			y++;
		}
		else{
			set[y*width+x] = var;
			x++;
		}
		var = popLinked(list);
		
	}
	
	setData *data = Malloc(sizeof(setData));
	data->height = height;
	data->width = width;
	data->setVars = set;
	
	// free startSetData, nothing in it
	destroyLinked(notParsed->set,NULL);
	Free(notParsed);
	return data;
}

treeNode *symNode(treeNode *newSymListNode,treeNode *symLists){

	nameData *cur = newSymListNode->data;
	int curName = cur->nameId;
	
	setData *setD = cur->set;
	int height = setD->height;
	int width = setD->width;
	int **set = setD->setVars;

	if(height > 1){
		printf("Error: Symbols Must Be On One Line.");
		exit(0);
	}	

	linkedList newSymList = createLinked(Malloc,Free);
	
	int i;
	for(i=0;i<width;i++)
		addTailLinked(newSymList,set[i]);
	
	symListInfo *newSym = Malloc(sizeof(symListInfo));
	newSym->nameId = curName;
	newSym->symbols = newSymList;

	if(!symLists){
		symLists = Malloc(sizeof(treeNode));
		symLists->data = createLinked(Malloc,Free);
	}
	
	linkedList *lists = symLists->data;
	addTailLinked(lists,newSym);
	
	Free(set);
	Free(setD);
	Free(cur);
	Free(newSymListNode);
	return symLists;
}

treeNode *storeNode(int tok,treeNode *set){

	nodeType type;
	switch(tok){
		case BOARD: 	type = boardType;	break;
		default:		assert(NULL,"Node Error");
	}
	startSetData *notParsed = set->data;
	setData *newData = createSet(notParsed);

	set->type = type;
	set->data = newData;
	return set;
}

treeNode *transNode(int type,treeNode *stagesNode,int transId,int objId,treeNode *startSet,treeNode *endSet){

	treeNode *newNode = Malloc(sizeof(treeNode));
	newNode->stages = NULL;
	transData *data = Malloc(sizeof(transData));
	
	if(stagesNode){
		newNode->stages = stagesNode->data;
		Free(stagesNode);
	}

	if(!transId)
		transId = inventName("Trans");

	data->transId = transId;
	data->objId = objId;
	
	startSetData *notParsedStart = startSet->data;
	startSetData *notParsedEnd = endSet->data;
	
	data->startData = createSet(notParsedStart);
	data->endData = createSet(notParsedEnd);
	
	// either Trans or TransSim
	if(type == TRANSFORM)
		newNode->type = transType;
	else
		newNode->type = transSimType;

	newNode->data = data;

	destroyLinked(startSet->spaces,singleFree);
	destroyLinked(endSet->spaces,singleFree);

	Free(startSet);
	Free(endSet);
	return newNode;
}

treeNode *setNode(int tok,treeNode *var,treeNode *set){

	if(!set){

		startSetData *startData = Malloc(sizeof(startSetData));
		startData->numLines = 1;
		startData->maxWidth = 0;
		startData->curWidth = 0;
		startData->set = createLinked(Malloc,Free);
		
		set = Malloc(sizeof(treeNode));
		set->spaces = createLinked(Malloc,Free);
		set->type = tempSetType;
		set->data = startData;
	}
	
	startSetData *sd = set->data;
	linkedList list = sd->set;

	if(tok == SPACEVAR){
		
		int *num = peekLinked(set->spaces);
		*num = *num + 1;
		return set;
	}

	if(tok == SEMI){
		pushLinked(list,ENDLINE);
		sd->numLines++;
		sd->curWidth = 0;
	}
	
	sd->curWidth++;
	if(sd->maxWidth < sd->curWidth)
		sd->maxWidth = sd->curWidth;
	
	void *data = var->data;
	pushLinked(list,data);
	Free(var);

	// for space
	int *num = Malloc(sizeof(int));
	*num = 0;
	pushLinked(set->spaces,num);
	return set;
}

// may need to create a treeNode to store elab
treeNode *setCommaNode(int tok,int varId,treeNode *varList){

	if(tok == CHARVAR){
		
		// assert no varlist
		assertBool(varList == NULL,"Char VarList");
		int *dataVar = Malloc(sizeof(int));
		*dataVar = varId;

		varList = Malloc(sizeof(treeNode));
		varList->type = charType;
		varList->data = dataVar;
		return varList;
	}
	if(tok == MANYVAR){
		if(!varList){
			
			manyData *many = Malloc(sizeof(manyData));
			linkedList brackVars = createLinked(Malloc,Free);
			many->brackVars = brackVars;

			varList = Malloc(sizeof(treeNode));
			varList->type = manyType;
			varList->data = many;
		}

		manyData *md = varList->data;
		linkedList list = md->brackVars;
		int *dataVar = Malloc(sizeof(int));
		*dataVar = varId;
		pushLinked(list,dataVar);
		return varList;
	}
	if(tok == ELABVAR || tok == ELABNEG){
		if(!varList){
			
			elabData *elab = Malloc(sizeof(elabData));
			linkedList negVars = createLinked(Malloc,Free);
			linkedList posVars = createLinked(Malloc,Free);
			elab->tempVarName = 0;
			elab->isAny = 0;
			elab->negVars = negVars;
			elab->posVars = posVars;

			varList = Malloc(sizeof(treeNode));
			varList->type = elabType;
			varList->data = elab;
		}
		
		elabData *ed = varList->data;
		linkedList addToList;
		if(tok == ELABNEG)
			addToList = ed->negVars;
		else
			addToList = ed->posVars;
		
		int *dataVar = Malloc(sizeof(int));
		*dataVar = varId;
		pushLinked(addToList,dataVar);
		return varList;
	}
	// error
	return NULL;
}

treeNode *setBoardVarNode(int tok,int varId,int sym){

	cellData *dataVar = Malloc(sizeof(cellData));
	dataVar->symList = NULL;
	dataVar->symListName = sym;
	dataVar->cellName = varId;

	treeNode *varList = Malloc(sizeof(treeNode));
	varList->data = dataVar;
	return varList;
}

treeNode *setVarNode(int tok,int varId,treeNode *varList){

	if(tok == CHARVAR){
		return setCommaNode(tok,varId,NULL);
	}
	if(tok == MANYVAR){
		return setCommaNode(tok,varId,NULL);
	}
	if(tok == ELABNEG){
		return setCommaNode(tok,varId,NULL);
	}
	if(tok == MANYBRACK){
		return varList;
	}
	if(tok == ELABPAREN){
		elabData *ed = varList->data;
		ed->tempVarName = 0;
		return varList;
	}

	// only elabtemp and elabcol can create tempvars 
	if(tok == ELABCOL){
		elabData *ed = varList->data;
		ed->tempVarName = varId;
		return varList;
	}
	if(tok == ELABTEMP){
		
		elabData *elab = Malloc(sizeof(elabData));
		elab->tempVarName = varId;
		elab->isAny = 0;
		elab->negVars = createLinked(Malloc,Free);
		elab->posVars = createLinked(Malloc,Free);

		varList = Malloc(sizeof(treeNode));
		varList->type = elabType;
		varList->data = elab;
		return varList;
	}
	if(tok == ELABQUEST){
		
		elabData *elab = Malloc(sizeof(elabData));
		elab->tempVarName = 0;
		elab->isAny = 1;
		elab->negVars = NULL;
		elab->posVars = NULL;

		varList = Malloc(sizeof(treeNode));
		varList->type = elabType;
		varList->data = elab;
		return varList;
	}
	// error
	return NULL;
}

treeNode *nameNode(int tok,treeNode *stagesNode,int nameId,int objId,treeNode *set){

	nodeType type;
	switch(tok){
		case OBJECT:		type = objType; 	break;
		case DESOBJECT:		type = desObjType; 	if(!nameId) nameId = inventName("DesObj");		break;
		case REQUIRE:		type = reqType; 	if(!nameId) nameId = inventName("Req");			break;
		case OPTION:		type = optType; 	if(!nameId) nameId = addSymbol("+NoNameOpt+");	break;
		case START:			type = startType;	break;
		case END:			type = endType;		break;
		case SYMBOLS: 		type = symType;		break;
		default:			assert(NULL,"No Token");
	}
	startSetData *notParsed = set->data;
	
	nameData *name = Malloc(sizeof(nameData));
	name->nameId = nameId;
	name->objId = objId;
	name->elabNum = 0;
	name->set = createSet(notParsed);
	
	treeNode *newNode = Malloc(sizeof(treeNode));
	newNode->type = type;
	newNode->data = name;
	newNode->stages = NULL;
	
	if(stagesNode){
		newNode->stages = stagesNode->data;
		Free(stagesNode);
	}
	
	destroyLinked(set->spaces,singleFree);
	Free(set);
	return newNode;
}

void freeSyms(void *data){
	stringData *newSym = data;
	Free(newSym->str);
	Free(newSym);
}

int addSymbol(char *sym){

	stringData *retSym = getLinked(symTable,findString,sym);
	if(retSym)
		return retSym->value;
	
	int len = strlen(sym);
	char *newStr = Malloc(sizeof(char)*(len+1));
	strcpy(newStr,sym);
	stringData *newSym = Malloc(sizeof(stringData));
	
	int nextVar = sizeLinked(symTable)+1;
	newSym->value = nextVar;
	newSym->str = newStr;
	
	pushLinked(symTable,newSym);	
	return nextVar;
}

int initSym(){

	symTable = createLinked(Malloc,Free);
	return 0;
}

int yywrap(){
	
	endFile = 1;
	return 1;
}

void yyerror(char *s) {

	printf("Error: Syntax Error On Line %i.\n",curLineNum);
	exit(0);
}

void endError(char *msg){
	printf("Error: %s\n",msg);
	printf("Use --help For More Information\n\n");
	exit(0);
}

void endHelp(){

	printf("usage: sabr [--flag] <number of stages> <path to source>\n");
	printf("example: sabr --all 20 < source.tb\n\n");
	printf("flags:\n");
	printf("\t\tNo flag produces the result output\n");
	printf("cnf\t\tProduces the cnf.txt containing the conjunctive normal form\n");
	printf("debug\t\tLike cnf, but will show cnf in more detail in debug.txt\n");
	printf("result\t\tSDesn't use minisat, assumes vars.out will come from other solver\n");
	printf("help\t\tHelp screen\n\n");
	exit(0);
}

char *getDir(char *path){

	int last = 0;
	int i;
	
	for(i=0;i<strlen(path);i++)
		if(path[i] == '/')
			last = i+1;
	
	char *dir = Malloc(sizeof(char)*(last+1));
	strncpy(dir,path,last);
	
	return dir;
}

void fileRead(char *file){

	// open a file handle to a particular file:
	FILE *myfile = fopen(file,"r");
	
	// make sure it's valid:
	if (!myfile) {
		endError("Source File Does Not Exist");
	}
	
	// set lex to read from it instead of defaulting to STDIN
	yyin = myfile;
}

int processFlags(int argc,char **argv){

	int a=1;
	flag = FLAG_RUN;

	// while processing flags
	while(a < argc && argv[a][0] == '-' && argv[a][1] == '-'){
	
		if(strcmp(argv[a],"--help") == 0){
			endHelp();
		}
		else if(strcmp(argv[a],"--debug") == 0){	
			flag = FLAG_DEBUG;
		}
		else if(strcmp(argv[a],"--cnf") == 0){		
			flag = FLAG_CNF;
		}
		else if(strcmp(argv[a],"--result") == 0){	
			flag = FLAG_RESULT;
		}
		else{
			endError("Invalid Flag");
		}
		a++;
	}
	
	return a;
}

int main(int argc,char **argv){
	
	if(argc == 1){
		endHelp();
	}
	
	sabrDir = getDir(argv[0]);
	
	// current argument
	int a = processFlags(argc,argv);
	
	if(a >= argc || !atoi(argv[a])){
		endError("Positive Integer Number Of Levels Must Be Input First");
	}
	
	curLineNum = 1;
	numStages = atoi(argv[a]);
	inventNameNum = 0;
	endFile = 0;
	
	a++;
	if(a >= argc){
		endError("Must Enter Source File");
	}
	
	char *file = argv[a];
	fileRead(file);
	
	a++;
	if(a != argc){
		endError("Too Many Arguments");
	}
	
	initSym();
	printf("Start\n");

	yyparse();

	destroyLinked(symTable,freeSyms);
	// could use Malloc-L, Free-L and MemInfo to show no memory lost
	// should say: "Leak Size: 0"

	return 0;
}
