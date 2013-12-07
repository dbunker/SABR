#include <stdlib.h>
#include "botlist.h"

/* internal use */
typedef struct node_t{
	struct node_t *prev;
	struct node_t *next;
	void* data;
} node;

// create node (need to give it malloc space of sizeNode size)
void createNode(linkedNode curP,void *data){
	node *cur = curP;
	cur->prev = NULL;
	cur->next = NULL;
	cur->data = data;
}

int sizeNode(){
	return sizeof(node);
}

// put data in or get data out of node
// embedNode is like replaceNode
void embedNode(linkedNode curP,void *data){
	node *cur = curP;
	cur->data = data;
}

void *extractNode(linkedNode curP){
	node *cur = curP;
	return cur->data;
}

// movement
linkedNode getPrevNode(linkedNode curP){
	node *cur = curP;
	return cur->prev;
}

linkedNode getNextNode(linkedNode curP){
	node *cur = curP;
	return cur->next;
}

// insert
void insertAfterNode(linkedNode curP,linkedNode insP){
	node *cur = curP;
	node *ins = insP;
	
	ins->prev = cur;
	ins->next = cur->next;
		
	if(cur->next)
		cur->next->prev = ins;
	cur->next = ins;
}

void insertBeforeNode(linkedNode curP,linkedNode insP){
	node *cur = curP;
	node *ins = insP;
	
	ins->prev = cur->prev;
	ins->next = cur;
	
	if(cur->prev)
		cur->prev->next = ins;
	cur->prev = ins;
}

// remove
void removeNode(linkedNode curP){
	node *cur = curP;
	if(cur->prev)
		cur->prev->next = cur->next;
	if(cur->next)
		cur->next->prev = cur->prev;
}

void connectNode(linkedNode ln1,linkedNode ln2){
	node *n1 = ln1;
	node *n2 = ln2;
	
	n2->prev = n1;
	n1->next = n2;
}

// continues until function returns 0 (same as execUntilNode)
linkedNode execUntilNode(linkedNode curP,int (*compare)(void*,linkedNode),void *param){	
	node *cur = curP;

	while(cur){
		if(compare(param,cur) == 0)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

