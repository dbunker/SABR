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

// this file contains all of the searching functions

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

// free
void singleFree(void *data){
	Free(data);
}

// simple int
int intSearch(void *param,void *data){

	int *pInt = param;
	int *dInt = data;

	if(*pInt == *dInt) 
		return 0;
	return -1;
}

// print
void simplePrint(void *data){
	printf("%p\n",data);
}

// compare
int simpleComp(void *first,void *second){
	if(first > second)
		return 1;
	if(first < second)
		return -1;
	return 0;
}

// simple
int simpleSearch(void *param,void *data){

	if(param == data) 
		return 0;
	return -1;
}

// stringData
int findString(void *param,void *data){
	
	stringData *sym = data;
	char *str = sym->str;
	return strcmp((char*)param,str);
}

// stringData
int findValue(void *param,void *data){
	
	int intParam = *(int*)param;
	stringData *str = data;
	return !(str->value == intParam);
}

// stringData
char *getStringSym(int value){

	stringData *data = getLinked(symTableGlobal,findValue,&value);
	assert(data,"StringSym Does Not Exist");
	return data->str;
}

int findTemp(void *param,void *data){
	int paramTempName = *((int*)param);
	tempElem *elem = data;

	if(elem->tempId == paramTempName)
		return 0;
	return -1;
}

// tempSym
int findSym(void *param,void *data){

	int *testSymP = param;
	int testSym = *testSymP;
	
	tempSym *listData = data;
	if(listData->symId == testSym)
		return 0;
	return -1;
}
