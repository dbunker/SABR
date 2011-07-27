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

/* this is a general link list interface
 * the motivation of this interface is to provide functionality 
 * while minimizing the node twidling normally associated with linked 
 * lists, although this sometimes comes at the expense of efficiency
 * possible return values:
 * 0 or Pointer to Retrieved Data (success)
 * -1 or NULL 		if tried to retrieve data, but unable because data was
 * 			not present or linkedlist, function, or data was NULL (failure)
 * -2 			if malloc space error occured other than createLinked (failure)
 * NULL			if malloc space error occured in createLinked (failure)
 * linklist always a parameter
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define FUNC_ERROR -1
#define MEM_ERROR -2

/* linked list and nodes are internal */
typedef void *linkedList;

/* @desc allocate space and create linkedlist
 * @param malloc and free functions to be used
 * @return linkedlist (no malloc) */
linkedList createLinked(void*(*)(size_t),void(*)(void*));

/* @desc size
 * @param standard
 * @return size (no malloc) */
int sizeLinked(linkedList);
/* @desc create array of list
 * @param standard
 * @return array (uses malloc) */
void *toArrayLinked(linkedList);
/* @desc free
 * @param function freeData(data)
 * @return (no malloc) */
int destroyLinked(linkedList,void(*)(void*));

/* @desc pushes data
 * @param value to push
 * @return (uses malloc) */
int pushLinked(linkedList,void*);
/* @desc pops data
 * @param standard
 * @return popped data (no malloc) */
void *popLinked(linkedList);
/* @desc head data
 * @param standard
 * @return head data (no malloc) */
void *peekLinked(linkedList);
/* @desc add data
 * @param value to add
 * @return (uses malloc) */
int addTailLinked(linkedList,void*);
/* @desc remove data
 * @param standard
 * @return (no malloc) */
void *removeTailLinked(linkedList);
/* @desc tail data
 * @param standard
 * @return tail data (no malloc) */
void *tailLinked(linkedList);

/* @desc insert value into sorted list */
/* @param function compareTo(param,data), the param field
 * @return (uses malloc) */
int insertSortLinked(linkedList,int(*)(void*,void*),void*);
/* @desc sort the unsorted list
 * @param function compareTo(param,data), the param field
 * @return (no malloc) */
int sortLinked(linkedList,int(*)(void*,void*));

/* @desc get value
 * @param function compareTo(param,data), the param field
 * @return data pointer that matches function (no malloc) */
void *getLinked(linkedList,int(*)(void*,void*),void*);
/* @desc remove value
 * @param function compareTo(param,data), the param field
 * @return data pointer that matched function (no malloc) */
void *removeLinked(linkedList,int(*)(void*,void*),void*);
/* @desc insert before value
 * @param function compareTo(param,data), the param field, to insert data pointer
 * @return (uses malloc) */
int insertBeforeLinked(linkedList,int(*)(void*,void*),void*,void*);
/* @desc insert after value
 * @param function compareTo(param,data), the param field, to insert data pointer
 * @return (uses malloc) */
int insertAfterLinked(linkedList,int(*)(void*,void*),void*,void*);
/* @desc replace value
 * @param function compareTo(param,data), the param field, replacement data pointer
 * @return data pointer that matched function (no malloc) */
void *replaceLinked(linkedList,int(*)(void*,void*),void*,void*);

/* @desc executeOn executed on each until executeOn return non 0 or end of file
 * @param function executeOn(param,data), the param field
 * @return (no malloc) */
int execUntilLinked(linkedList,int(*)(void*,void*),void*);

/* @desc reverse list 
 * @param standard
 * @return (no malloc) */
int reverseLinked(linkedList);
/* @desc attach second linked list to end of first
 * @param linked lists
 * @return combined linked list (no malloc) */
linkedList concatLinked(linkedList,linkedList);
/* @desc copy link list
 * @param linked list, malloc and free this new list will use, a copy function
 * @return new copy of linked list (uses malloc) */
linkedList copyLinked(linkedList,void *(*)(size_t),void (*)(void*),void *(*)(void*));
/* @desc print data
 * @param function print(data)
 * @return (no malloc) */
int printLinked(linkedList,void(*)(void*));

#endif
