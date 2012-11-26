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

/* linkedlist implementation */

#include <stdio.h>
#include <stdlib.h>
#include "botlist.h"
#include "linkedlist.h"
#include "gendebug.h"

/* internal use */
typedef struct{
	linkedNode head;
	linkedNode tail;
	unsigned int size;
	void *(*myMalloc)(size_t);
	void (*myFree)(void*);
	void **array;
	/* indicates list has changed since the array was produced */
	int isChanged;
} linked;

linkedList createLinked(void *(*myMalloc)(size_t),void (*myFree)(void*)){

	/* create and initialize list */
	if(!myMalloc)
		myMalloc = malloc;
	if(!myFree)
		myFree = free;

	linked *list = myMalloc(sizeof(linked));
	if(!list) return NULL;

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->myMalloc = myMalloc;
	list->myFree = myFree;
	list->array = NULL;
	return list;
}

int sizeLinked(linkedList listP){

	linked *list = listP;
	assert(list,"link");
	return list->size;
}

/* internal use */
typedef struct{
	void **array;
	int curPos;
} arrayData;

/* internal use */
int createArray(void *param,void *data){

	arrayData *ar = param;
	ar->array[ar->curPos] = data;
	ar->curPos++;
	return 0;
}

void *toArrayLinked(linkedList listP){

	linked *list = listP;
	assert(list,"link");

	/* if it changed, it needs to be remade */
	if(list->isChanged){
		if(list->array){
			list->myFree(list->array);
			list->array = NULL;
		}
		list->isChanged = 0;
	}

	/* array momoization */
	if(list->array)
		return list->array;

	int size = sizeLinked(list);
	if(size <= 0) 
		return NULL;
	void **array = list->myMalloc(sizeof(void*)*size);

	arrayData ar;
	ar.array = array;
	ar.curPos = 0;
	execUntilLinked(list,createArray,&ar);
	list->array = array;
	return array;
}

int destroyLinked(linkedList listP,void (*freeData)(void*)){

	linked *list = listP;
	assert(list,"link");

	/* pop and free all data */
	void *data;
	while((data = popLinked(list)))
		if(freeData)
			freeData(data);

	if(list->array)	
		list->myFree(list->array);

	list->myFree(list);
	return 0;
}

int pushLinked(linkedList listP,void *data){

	linked *list = listP;
	assert(list,"link");
	assert(data,"link");

	linkedNode newHead = list->myMalloc(sizeNode());
	if(!newHead) 
		return MEM_ERROR;
	list->isChanged = 1;

	/* set head as next */
	createNode(newHead,data);

	if(list->head)
		insertBeforeNode(list->head,newHead);

	/* set new head */
	list->head = newHead;
	list->size++;

	/* if there is not a tail, set it */
	if(!list->tail)
		list->tail = newHead;

	return 0;
}

void *popLinked(linkedList listP){

	linked *list = listP;
 	assert(list,"link");

	linkedNode curHead = list->head;
	if(!curHead) 
		return NULL;
	list->isChanged = 1;

	/* get head as return and set to next */
	void *returnData = extractNode(curHead);
	list->head = getNextNode(curHead);
	list->size--;	

	/* if there is not a head, remove tail */
	if(!list->head)
		list->tail = NULL;

	removeNode(curHead);
	list->myFree(curHead);
	return returnData;
}

void *peekLinked(linkedList listP){

	linked *list = listP;
	assert(list,"link");

	if(!list->head)
		return NULL;

	return extractNode(list->head);
}

int addTailLinked(linkedList listP,void *data){

	linked *list = listP;
	assert(list,"link");
	assert(data,"link");

	linkedNode curTail = list->tail;
	list->isChanged = 1;

	if(!curTail)
		return pushLinked(list,data);

	linkedNode newTail = list->myMalloc(sizeNode());
	if(!newTail) 
		return MEM_ERROR;

	/* set tail after curTail */
	createNode(newTail,data);

	insertAfterNode(curTail,newTail);
	list->tail = newTail; 
	list->size++;
	return 0;
}

void *removeTailLinked(linkedList listP){

	linked *list = listP;
 	assert(list,"link");

	linkedNode curTail = list->tail;
	if(!curTail) 
		return NULL;
	list->isChanged = 1;

	/* get head as return and set to next */
	void *returnData = extractNode(curTail);
	list->tail = getPrevNode(curTail);
	list->size--;	

	/* if there is not a tail, remove head */
	if(!list->tail)
		list->head = NULL;

	removeNode(curTail);
	list->myFree(curTail);
	return returnData;
}

void *tailLinked(linkedList listP){

	linked *list = listP;
	assert(list,"link");

	if(!list->tail)
		return NULL;

	return extractNode(list->tail);
}

/* internal use */
typedef struct{
	void *info;
	int (*func)(void*,void*);
} paramHolder;

/* internal use */
int sortCompareTo(void *compareToParam,void *data){

	paramHolder *hold = compareToParam;
	int (*compareTo)(void*,void*) = hold->func;
	void *newData = hold->info;

	/* this will cause insertBeforeLinked to continue to execute
           until the inputed data is larger than list data */
	if(newData != NULL && compareTo(newData,data) <= 0)
		return 0;
	return -1;
}

int insertSortLinked(linkedList listP,int (*compareTo)(void*,void*),void *data){

	linked *list = listP;
	assert(list,"link");
	assert(compareTo,"link");
	assert(data,"link");

	list->isChanged = 1;

	paramHolder hold;
	hold.info = data;
	hold.func = compareTo;

	/* if never larger, it goes at end */
	int ret = insertBeforeLinked(list,sortCompareTo,&hold,data);
	if(ret == MEM_ERROR)
		return MEM_ERROR;
	if(ret == -1)
		ret = addTailLinked(list,data);

	return ret;
}

/* internal use */
int sortInsert(void *listParam,void *data){

	paramHolder *hold = listParam;
	linked *list =  hold->info;
	int (*compareTo)(void*,void*) = hold->func;
	insertSortLinked(list,compareTo,data);
	return 0;
}

// use skip list
int sortLinked(linkedList listP,int (*compareTo)(void*,void*)){

	linked *list = listP;
	assert(list,"link");
	assert(compareTo,"link");

	linked *newList = createLinked(list->myMalloc,list->myFree);
	if(!newList)
		return MEM_ERROR;
	list->isChanged = 1;

	/* perform sort on each value to make a new list */
	paramHolder hold;
	hold.info = newList;
	hold.func = compareTo;
	execUntilLinked(list,sortInsert,&hold);

	list->head = newList->head;
	list->tail = newList->tail;
	list->size = newList->size;

	destroyLinked(newList,NULL);
	return 0;
}

void *getLinked(linkedList listP,int (*compareTo)(void*,void*),void *param){

	linked *list = listP;
	assert(list,"link");
	assert(compareTo,"link");

	/* iterate through list until match is found */
	linkedNode curHead = list->head;
	while(curHead){
		if(compareTo(param,extractNode(curHead)) == 0)
			return extractNode(curHead);
		curHead = getNextNode(curHead);
	}
	return NULL;
}

void *removeLinked(linkedList listP,int (*compareTo)(void*,void*),void *param){

	linked *list = listP;
	assert(list,"link");
	assert(compareTo,"link");

	list->isChanged = 1;

	/* iterate through list until match is found */
	linkedNode curHead = list->head;
	linkedNode prevHead = NULL;
	while(curHead){
		if(compareTo(param,extractNode(curHead)) == 0){
			if(curHead == list->head)
				return popLinked(list);
			if(curHead == list->tail)
				list->tail = prevHead;

			removeNode(curHead);

			void *retData = extractNode(curHead);
			list->size--;
			list->myFree(curHead);
			return retData;
		}
		prevHead = curHead;
		curHead = getNextNode(curHead);
	}
	return NULL;
}

int insertBeforeLinked(linkedList listP,int (*compareTo)(void*,void*),void *param,void *data){

	linked *list = listP;
	assert(list,"link");
	assert(compareTo,"link");
	assert(data,"link");

	list->isChanged = 1;

	/* iterate through list until match is found */
	linkedNode curHead = list->head;
	
	while(curHead){
		if(compareTo(param,extractNode(curHead)) == 0){
			if(curHead == list->head)
				return pushLinked(list,data);

			linkedNode newNode = list->myMalloc(sizeNode());
			if(!newNode) 
				return MEM_ERROR;

			/* set node */
			createNode(newNode,data);
			insertBeforeNode(curHead,newNode);
			list->size++;
			return 0;
		}
		
		curHead = getNextNode(curHead);
	}
	return -1;
}

int insertAfterLinked(linkedList listP,int (*compareTo)(void*,void*),void *param,void *data){

	linked *list = listP;
	assert(list,"link");
	assert(compareTo,"link");
	assert(data,"link");

	list->isChanged = 1;

	/* iterate through list until match is found */
	linkedNode curHead = list->head;
	
	while(curHead){
		if(compareTo(param,extractNode(curHead)) == 0){
			if(curHead == list->tail)
				return addTailLinked(list,data);

			linkedNode newNode = list->myMalloc(sizeNode());
			if(!newNode) 
				return MEM_ERROR;

			/* set node */
			createNode(newNode,data);
			insertAfterNode(curHead,newNode);
			list->size++;
			return 0;
		}
		
		curHead = getNextNode(curHead);
	}
	return -1;
}

void *replaceLinked(linkedList listP,int (*compareTo)(void*,void*),void *param,void *data){

	linked *list = listP;
	assert(list,"link");
	assert(compareTo,"link");
	assert(data,"link");

	list->isChanged = 1;

	/* iterate through list until match is found */
	linkedNode curHead = list->head;
	while(curHead){
		if(compareTo(param,extractNode(curHead)) == 0){
			void *retData = extractNode(curHead);
			embedNode(curHead,data);
			return retData;
		}
		curHead = getNextNode(curHead);
	}
	return NULL;
}

int execUntilLinked(linkedList listP,int (*executeOn)(void*,void*),void *param){

	linked *list = listP;
	assert(list,"link");
	assert(executeOn,"link");
	int ret;

	/* iterate through list until match is found */
	linkedNode curHead = list->head;
	while(curHead){
		ret = executeOn(param,extractNode(curHead));
		if(ret != 0)
			return ret;
		curHead = getNextNode(curHead);
	}
	return 0;
}

int reverseLinked(linkedList listP){

	linked *list = listP;
	assert(list,"link");

	list->isChanged = 1;

	linked *newList = createLinked(list->myMalloc,list->myFree);
	if(!newList) 
		return MEM_ERROR;

	/* pop off one and onto other linked list */
	void *data;
	while((data = popLinked(list)))
		pushLinked(newList,data);

	list->head = newList->head;
	list->tail = newList->tail;
	list->size = newList->size;

	list->myFree(newList);
	return 0;
}

/* two have same malloc and free
 * the two cannot be the same list */
linkedList concatLinked(linkedList listP1,linkedList listP2){

	linked *list1 = listP1;
	linked *list2 = listP2;
	assert(list1,"link");
	assert(list2,"link");

	assertBool((list1 != list2),"link");
	assertBool((list1->myMalloc == list2->myMalloc),"link");
	assertBool((list1->myFree == list2->myFree),"link");

	if(sizeLinked(list1) == 0){
		list1->myFree(list1);
		return list2;
	}
	if(sizeLinked(list2) == 0){
		list2->myFree(list2);
		return list1;
	}

	connectNode(list1->tail,list2->head);
	list1->tail = list2->tail;

	list1->isChanged = 1;
	list1->size = list1->size + list2->size;

	list2->myFree(list2);
	return list1;
}

typedef struct{
	linkedList info;
	void *(*func)(void *);
} copyParam;

/* internal use */
int internalCopy(void *param,void *data){

	copyParam *cop = param;
	linkedList newList = cop->info;

	/* will do shallow copy if there is no function input */
	void *newData = param;
	if(cop->func)
		newData = cop->func(data);

	if(!newData)
		return -1;

	/* returns 0 when successful */
	int ret = addTailLinked(newList,newData);
	return ret;
}

linkedList copyLinked(linkedList listP,void *(*myMalloc)(size_t),void (*myFree)(void*),void *(*myCopy)(void*)){

	linked *list = listP;
	assert(list,"link");

	copyParam param;
	param.info = createLinked(myMalloc,myFree);
	if(!param.info)
		return NULL;
	param.func = myCopy;

	int ret = execUntilLinked(list,internalCopy,&param);
	if(ret != 0)
		return NULL;

	return param.info;
}

/* internal use */
int noParamExecVoid(void *execParam,void *data){

	void (*exec)(void*) = execParam;
	exec(data);
	return 0;
}

int printLinked(linkedList listP,void (*printOut)(void*)){

	linked *list = listP;
	assert(list,"link");
	assert(printOut,"link");

	/* run printOut on all */
	return execUntilLinked(list,noParamExecVoid,printOut);
}