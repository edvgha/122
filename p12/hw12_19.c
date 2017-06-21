#include "csapp.h"

int writable;

int readcnt;
sem_t mutex, w;

void* reader(void* vargp)
{
    while(1) {
        P(&mutex);
        readcnt++;
        if (readcnt == 1)
            P(&w);
        V(&mutex);

        printf("Read : %d\n", writable);

        P(&mutex);
        readcnt--;
        if (readcnt == 0)
            V(&w);
        V(&mutex);
    }
}

void* writer(void* vargp)
{
    while(1) {
        P(&w);

        printf("Write : %d\n", ++writable);

        V(&w);
    }
}

int main()
{
    readcnt = 0;
    Sem_init(&mutex, 0, 1);
    Sem_init(&w, 0, 1);

    pthread_t tid1, tid2;
    Pthread_create(&tid1, NULL, writer, NULL);
    Pthread_create(&tid2, NULL, reader, NULL);
    Pthread_exit(NULL);
}
