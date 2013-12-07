// this creates a basic doubly linked list
// all set to inline

#ifndef BOTLIST_H
#define BOTLIST_H

typedef void *linkedNode;

// create node (need to give it malloc space of sizeNode size)
void createNode(linkedNode,void*);
int sizeNode();

// put data in or get data out of node
// embedNode is like replaceNode
void embedNode(linkedNode,void*);
void *extractNode(linkedNode);

// movement
linkedNode getPrevNode(linkedNode);
linkedNode getNextNode(linkedNode);

// insert
void insertAfterNode (linkedNode,linkedNode);
void insertBeforeNode(linkedNode,linkedNode);

// remove
void removeNode(linkedNode);

// connect
void connectNode(linkedNode,linkedNode);

// continues until function returns 0 (same as getNode)
linkedNode execUntilNode(linkedNode,int(*)(void*,linkedNode),void*);

#endif
