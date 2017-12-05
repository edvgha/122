#include <sys/types.h>
#include <sys/syscall.h>

#include "csapp.h"

#define N 3

int writable;

sem_t counter, mutex, w;

void* reader(void* vargp)
{
    while(1) {
        P(&counter);
        P(&w);

        pid_t id = syscall(__NR_gettid);
        printf("%d Read : %d\n", (int)id, writable);
        Sleep(1);

        V(&w);
        V(&mutex);
    }
}

void* writer(void* vargp)
{
    while(1) {
        P(&mutex);
        P(&w);

        pid_t id = syscall(__NR_gettid);
        printf("%d Write : %d\n", (int)id, ++writable);
        Sleep(1);

        V(&w);
        V(&counter);
    }
}

int main()
{
    Sem_init(&counter, 0, N);
    Sem_init(&mutex, 0, 0);
    Sem_init(&w, 0, 1);

    pthread_t tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8;

    Pthread_create(&tid2, NULL, reader, NULL);
    Pthread_create(&tid3, NULL, reader, NULL);
    Pthread_create(&tid4, NULL, reader, NULL);

    Pthread_create(&tid1, NULL, writer, NULL);
    Pthread_exit(NULL);
}
