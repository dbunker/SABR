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
