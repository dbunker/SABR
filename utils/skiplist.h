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
