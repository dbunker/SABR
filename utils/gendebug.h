#ifndef GENDEBUG_H
#define GENDEBUG_H

#define MEM_ERROR -2

int globalLogSetting;

char *combineStrArr(char**,int);
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
