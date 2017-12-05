#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "csapp.h"

/* $begin thread_pool */
typedef struct {
    pthread_t *threads;   /* Threads array */         
    int n;                /* Number of threads */
    void* (*task) (void*);/* Thread's task */
    sem_t mutex;          /* Protects accesses to thread pool */
} thread_pool_t;
/* $end thread_pool */

void thread_pool_init(thread_pool_t *tp, int n, void* (func)(void* ));
void thread_pool_halve(thread_pool_t *tp);
void thread_pool_double(thread_pool_t *tp);

#endif /* __THREAD_POOL__ */
