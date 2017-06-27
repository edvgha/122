/* $begin thread_poolc */
#include "csapp.h"
#include "thread_pool.h"

#define MAX_NTHREADS 512
#define MIN_NTHREADS 1

/* Create thread pool with n threads and with 'func' task */
/* $begin thread_pool_init */
void thread_pool_init(thread_pool_t *tp, int n, void* (*func)(void*))
{
    tp->threads = Malloc(sizeof(pthread_t) * n);
    tp->n = n;
    tp->task = func;
    for (int i = 0; i < n; ++i)
        Pthread_create(&tp->threads[i], NULL, func, NULL);
    Sem_init(&tp->mutex, 0, 1);
}
/* $end thread_pool_init */

/* Double number of threads in thread pool */
/* $begin thread_pool_double */
void thread_pool_double(thread_pool_t *tp)
{
    P(&tp->mutex);

    if (tp -> n == MAX_NTHREADS) {
        V(&tp->mutex);
        return;
    }

    printf("THREAD POLL IS DOUBLING ... %d\n", tp->n);
    tp->threads = Realloc(tp->threads, sizeof(pthread_t) * (tp->n + tp->n));
    for (int i = 0; i < tp -> n; ++i)
        Pthread_create(&tp->threads[i + tp->n], NULL, tp->task, NULL);
    tp->n = (tp -> n + tp -> n);

    V(&tp->mutex);
}
/* $end thread_pool_double */

/* Halve number of threads in thread pool */
/* $begin thread_pool_halve */
void thread_pool_halve(thread_pool_t *tp)
{
    P(&tp->mutex);

    if (tp -> n == MIN_NTHREADS) {
        V(&tp->mutex);
        return ;
    }

    printf("THREAD POLL IS HALVING ... %d\n", tp->n);
    int k = (tp->n) >> 1;
    for (int i = k; i < tp->n; ++i)
        Pthread_cancel(tp->threads[i]);
    tp->threads = Realloc(tp->threads, sizeof(pthread_t) * k);
    tp->n = k;

    V(&tp->mutex);
}
/* $end thread_pool_halve */
/* $end thread_poolc*/
