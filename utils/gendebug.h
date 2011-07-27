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

#ifndef GENDEBUG_H
#define GENDEBUG_H

#define MEM_ERROR -2

int globalLogSetting;

void assert(void *nonZero,char *str);
void assertBool(int nonZero,char *str);
void *Malloc(size_t len);
void Free(void *mem);
void *MallocInfoL(size_t len,char *info);
void *MallocL(size_t len);
void *MallocSpecL(size_t len);
void FreeL(void *mem);
void MemInfo();

#endif
