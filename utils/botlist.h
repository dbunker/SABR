// this creates a basic doubly linked list
// all set to inline

#ifndef BOTLIST_H
#define BOTLIST_H

typedef void *linkedNode;

// create node (need to give it malloc space of sizeNode size)
inline void createNode(linkedNode,void*);
inline int sizeNode();

// put data in or get data out of node
// embedNode is like replaceNode
inline void embedNode(linkedNode,void*);
inline void *extractNode(linkedNode);

// movement
inline linkedNode getPrevNode(linkedNode);
inline linkedNode getNextNode(linkedNode);

// insert
inline void insertAfterNode (linkedNode,linkedNode);
inline void insertBeforeNode(linkedNode,linkedNode);

// remove
inline void removeNode(linkedNode);

// connect
inline void connectNode(linkedNode,linkedNode);

// continues until function returns 0 (same as getNode)
inline linkedNode execUntilNode(linkedNode,int(*)(void*,linkedNode),void*);

#endif
