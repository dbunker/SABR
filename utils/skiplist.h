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

#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "linkedlist.h"
#include "botlist.h"

typedef void *skipList;

/* malloc free compare */
skipList createSkip(void* (*)(size_t),void (*)(void*),int (*)(void*,void*));
int destroySkip(skipList,void(*)(void*));
int sizeSkip(skipList);

int insertSkip(skipList,void*);
void *getSkip(skipList,void*);
void *removeSkip(skipList,void*);

void *popSkip(skipList);
void *removeTailSkip(skipList);
int execUntilSkip(skipList,int (*)(void*,void*),void*);

void printSkip(skipList,void (*)(void*));
linkedList linkedSkip(skipList);

#endif
