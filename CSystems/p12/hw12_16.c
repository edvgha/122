#include "csapp.h"

void* thread(void *vargp);

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <nthreads>\n", argv[0]);
        exit(0);
    }
    int nthreads = atoi(argv[1]);
    pthread_t tid;
    pthread_t* tids = Malloc(sizeof(pthread_t) * nthreads);
    for (int i = 0; i < nthreads; ++i) {
        Pthread_create(&tids[i], NULL, thread, NULL);
    }
    for (int i = 0; i < nthreads; ++i) {
        Pthread_join(tids[i], NULL);
    }
    Free(tids);
    exit(0);
}

void* thread(void* vargp)
{
    printf("Hello, world\n");
    return NULL;
}
