#ifndef __MM__
#define __MM__
#include "csapp.h"

extern int mm_init(void);
extern void* mm_malloc(size_t size);
extern void mm_free(void* ptr);
extern void display();

#endif //__MM__
