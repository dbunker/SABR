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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "botlist.h"
#include "linkedlist.h"
#include "skiplist.h"
#include "gendebug.h" 

#define NUM_LISTS 32
int globalSkipSeed = 0;

/* internal use */
typedef struct infoNode_t{
	int nodeLevel;
	int curLevel;
	void *data;
	linkedNode down;
} nodeInfo;

/* internal use */
typedef struct{
	linkedNode *heads;
	int size;
	void *(*myMalloc)(size_t);
	void (*myFree)(void*);
	int (*myCompare)(void*,void*);
} skip;

skipList createSkip(void* (*myMalloc)(size_t),void (*myFree)(void*),int (*myCompare)(void*,void*)){
	
	assert(myCompare,"skip");
	
	if(!myMalloc)
		myMalloc = malloc;
	if(!myFree)
		myFree = free;
	
	if(!globalSkipSeed){
		globalSkipSeed = (unsigned) time(NULL);
		srand(globalSkipSeed);
	}

	skip *sList = myMalloc(sizeof(skip));
	sList->size = 0;
	sList->myMalloc = myMalloc;
	sList->myFree = myFree;
	sList->myCompare = myCompare;

	linkedNode *heads = myMalloc(NUM_LISTS*sizeNode());
	int i;
	for(i=0;i<NUM_LISTS;i++){

		nodeInfo *info = myMalloc(sizeof(nodeInfo));
		info->curLevel = i;
		info->nodeLevel = NUM_LISTS-1;
		info->data = NULL;

		info->down = NULL;
		if(i>0)
			info->down = heads[i-1];
		linkedNode newNode = myMalloc(sizeNode());
		createNode(newNode,info);

		heads[i] = newNode;
	}
	sList->heads = heads;
	return sList;
}

int destroySkip(skipList sListP,void (*freeData)(void*)){

	skip *sList = sListP;
	assert(sList,"skip");

	// pop and free all data
	void *data;
	while((data = popSkip(sList)))
		if(freeData)
			freeData(data);
	
	int i;
	linkedNode *heads = sList->heads;
	for(i=0;i<NUM_LISTS;i++){
		linkedNode node = heads[i];

		linkedNode next = getNextNode(node);
		assertBool((next == NULL),"skip");

		nodeInfo *info = extractNode(node);
		sList->myFree(info);
		sList->myFree(node);
	}

	sList->myFree(heads);
	sList->myFree(sList);
	return 0;
}

int sizeSkip(skipList sListP){

	skip *sList = sListP;
	assert(sList,"skip");
	return sList->size;
}

/* internal use */
int randLevel(){

	// odds half for each additional level
	int level = 0;
	while(rand()%2 && level < NUM_LISTS-1)
		level++;
	return level;
}

/* internal use */
typedef struct{
	int (*compare)(void*,void*);
	void *data;
} holdParam;

/* internal use */
int findLargerNode(void *paramP,void *prevTestNodeD){

	linkedNode prevTestNode = prevTestNodeD;
	holdParam *param = paramP;
	linkedNode testOnNode = getNextNode(prevTestNode);

	// last node in list
	if(!testOnNode)
		return 0;
	
	nodeInfo *testOnInfo = extractNode(testOnNode);
	void *testOnData = testOnInfo->data;
	
	// if this node is greater than the inputted parameter
	if(param->compare(param->data,testOnData) >= 0)
		return 0;

	return -1;
}

// error if an item already has that key (compare returns 0)
int insertSkip(skipList sListP,void *data){

	skip *sList = sListP;
	assert(sList,"skip");
	assert(data,"skip");

	linkedNode *heads = sList->heads;
	int nodeLevel = randLevel();

	int curLevel = NUM_LISTS-1;
	linkedNode curHead = heads[curLevel];
	nodeInfo *prevInfo = NULL;

	holdParam paramData;
	paramData.compare = sList->myCompare;
	
	while(curLevel >= 0){

		paramData.data = data;
		linkedNode justLess = execUntilNode(curHead,findLargerNode,&paramData);

		// test if value already exists
		if(justLess){
			linkedNode testNode = getNextNode(justLess);
			if(testNode){
				nodeInfo *testInfo = extractNode(testNode);
				if(sList->myCompare(data,testInfo->data) == 0){
					// throw error
					assert(NULL,"skip");
					return -1;
				}
			}
		}

		// only need to add the node to the list if curLevel is at its level or below
		if(curLevel <= nodeLevel){

			nodeInfo *info = sList->myMalloc(sizeof(nodeInfo));
			info->curLevel = curLevel;
			info->nodeLevel = nodeLevel;
			info->data = data;
			info->down = NULL;

			linkedNode newNode = sList->myMalloc(sizeNode());
			createNode(newNode,info);

			if(prevInfo)
				prevInfo->down = newNode;
			prevInfo = info;

			insertAfterNode(justLess,newNode);
		} 
		
		// info is only empty if justLess is the head node
		nodeInfo *info = extractNode(justLess);
		curHead = info->down;
		curLevel--;
	}
	sList->size++;
	return 0;
}

/* internal use */
/* values are represented as pillars whose size is determinned randomly throughout the 
 * list, the top of the piller points down to lower levels, all values in a pillar are the same, 
 * this returns the top node of a piller */
linkedNode getFirstNodeSkip(skip *sList,int (*compare)(void*,void*),void *data){

	linkedNode *heads = sList->heads;
	int curLevel = NUM_LISTS-1;
	linkedNode curHead = heads[curLevel];

	holdParam paramData;
	paramData.compare = compare;
	
	while(curLevel >= 0){

		paramData.data = data;
		linkedNode justLess = execUntilNode(curHead,findLargerNode,&paramData);

		// get
		linkedNode testOnNode = getNextNode(justLess);
		if(testOnNode){
			nodeInfo *testOnInfo = extractNode(testOnNode);
			void *testOnData = testOnInfo->data;
			if(testOnData && compare(data,testOnData) == 0)
				return testOnNode;
		}

		// info is only empty if justLess is the head node
		nodeInfo *info = extractNode(justLess);
		curHead = info->down;
		curLevel--;
	}
	return NULL;
}

void *getSkip(skipList sListP,void *data){

	skip *sList = sListP;
	assert(sList,"skip");
	assert(data,"skip");

	linkedNode testOnNode = getFirstNodeSkip(sListP,sList->myCompare,data);
	if(!testOnNode)
		return NULL;
	
	nodeInfo *testOnInfo = extractNode(testOnNode);
	void *retData = testOnInfo->data;
	return retData;
}

/* internal use */
void *removeSkipInt(skip *sList,int (*compare)(void*,void*),void *data){

	linkedNode testOnNode = getFirstNodeSkip(sList,compare,data);
	if(!testOnNode)
		return NULL;
	
	nodeInfo *testOnInfo = extractNode(testOnNode);
	void *retData = testOnInfo->data;
	
	linkedNode newNode;
	while(testOnNode){
		
		removeNode(testOnNode);
		testOnInfo = extractNode(testOnNode);
		newNode = testOnInfo->down;

		sList->myFree(testOnInfo);
		sList->myFree(testOnNode);
		testOnNode = newNode;
	}

	sList->size--;
	return retData;
}

void *removeSkip(skipList sListP,void *data){

	skip *sList = sListP;
	assert(sList,"skip");
	assert(data,"skip");

	return removeSkipInt(sList,sList->myCompare,data);
}

/* internal use */
int numHops(void *param,void *data){
	
	int *sizep = param;
	int size = *sizep;
	*sizep = size + 1;
	return -1;
}

/* internal use */
int tooBig(void *param,void *data){
	
	int *sizep = param;
	int size = *sizep;
	
	if(size <= 0)
		return 0;
	*sizep = size - 1;
	return -1;
}

/* internal use */
int tooSmall(void *param,void *data){
	return 0;
}

void *popSkip(skipList sListP){
	skip *sList = sListP;
	assert(sList,"skip");

	return removeSkipInt(sList,tooSmall,NULL);
}

void *removeTailSkip(skipList sListP){
	skip *sList = sListP;
	assert(sList,"skip");

	// this is reduced to 0, at which point it has found the end of the list
	int size = 0;
	removeSkipInt(sList,numHops,&size);
	size = size-1;

	return removeSkipInt(sList,tooBig,&size);
}

int execUntilSkip(skipList sListP,int (*executeOn)(void*,void*),void *param){

	skip *sList = sListP;
	assert(sList,"skip");
	assert(executeOn,"skip");

	linkedNode mainListHead = sList->heads[0];
	linkedNode mainList = getNextNode(mainListHead);
	int ret;

	linkedNode curHead = mainList;
	while(curHead){
		nodeInfo *info = extractNode(curHead);
		ret = executeOn(param,info->data);
		if(ret != 0)
			return ret;
		curHead = getNextNode(curHead);
	}
	return 0;
}

int singleExec(void *param,void *data){

	void (*exec)(void*) = param;
	exec(data);
	return 0;
}

void printSkip(skipList sListP,void (*myPrint)(void*)){
	
	skip *sList = sListP;
	assert(sList,"skip");
	execUntilSkip(sList,singleExec,myPrint);
}

/* internal use */
int makeList(void *listP,linkedNode nodeD){

	linkedNode node = nodeD;
	linkedList list = listP;
	nodeInfo *info = extractNode(node);	
	void *data = info->data;
	addTailLinked(list,data);
	return -1;
}

linkedList linkedSkip(skipList sListP){

	skip *sList = sListP;
	assert(sList,"skip");

	linkedList newList = createLinked(sList->myMalloc,sList->myFree);
	linkedNode mainListHead = sList->heads[0];
	linkedNode mainList = getNextNode(mainListHead);

	execUntilNode(mainList,makeList,newList);
	return newList;
}
