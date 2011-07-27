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
#include "botlist.h"

/* internal use */
typedef struct node_t{
	struct node_t *prev;
	struct node_t *next;
	void* data;
} node;

// create node (need to give it malloc space of sizeNode size)
inline void createNode(linkedNode curP,void *data){
	node *cur = curP;
	cur->prev = NULL;
	cur->next = NULL;
	cur->data = data;
}

inline int sizeNode(){
	return sizeof(node);
}

// put data in or get data out of node
// embedNode is like replaceNode
inline void embedNode(linkedNode curP,void *data){
	node *cur = curP;
	cur->data = data;
}

inline void *extractNode(linkedNode curP){
	node *cur = curP;
	return cur->data;
}

// movement
inline linkedNode getPrevNode(linkedNode curP){
	node *cur = curP;
	return cur->prev;
}

inline linkedNode getNextNode(linkedNode curP){
	node *cur = curP;
	return cur->next;
}

// insert
inline void insertAfterNode(linkedNode curP,linkedNode insP){
	node *cur = curP;
	node *ins = insP;
	
	ins->prev = cur;
	ins->next = cur->next;
		
	if(cur->next)
		cur->next->prev = ins;
	cur->next = ins;
}

inline void insertBeforeNode(linkedNode curP,linkedNode insP){
	node *cur = curP;
	node *ins = insP;
	
	ins->prev = cur->prev;
	ins->next = cur;
	
	if(cur->prev)
		cur->prev->next = ins;
	cur->prev = ins;
}

// remove
inline void removeNode(linkedNode curP){
	node *cur = curP;
	if(cur->prev)
		cur->prev->next = cur->next;
	if(cur->next)
		cur->next->prev = cur->prev;
}

inline void connectNode(linkedNode ln1,linkedNode ln2){
	node *n1 = ln1;
	node *n2 = ln2;
	
	n2->prev = n1;
	n1->next = n2;
}

// continues until function returns 0 (same as execUntilNode)
inline linkedNode execUntilNode(linkedNode curP,int (*compare)(void*,linkedNode),void *param){	
	node *cur = curP;

	while(cur){
		if(compare(param,cur) == 0)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

