//*************************************************************************//
// ********************* see hw12_21 COMPLETELY FAILED ********************//
//*************************************************************************//
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
        //Sleep(1);

        P(&mutex);
        readcnt--;
        if (readcnt == 0)
            V(&w);
        V(&mutex);
    }
}

void* writer(void* vargp)
{
    int do_unlock = 0;
    while(1) {
        //P(&mutex);
        if (readcnt == 0) {
            P(&w);
            do_unlock = 1;
        }
        //V(&mutex);

        printf("Write : %d\n", ++writable);
        //Sleep(1);

        if (do_unlock == 1) {
            do_unlock = 0;
            V(&w);
        }
    }
}

int main()
{
    readcnt = 0;
    Sem_init(&mutex, 0, 1);
    Sem_init(&w, 0, 1);

    pthread_t tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8;
    Pthread_create(&tid2, NULL, reader, NULL);
    Pthread_create(&tid3, NULL, reader, NULL);
    Pthread_create(&tid4, NULL, reader, NULL);
    Pthread_create(&tid4, NULL, reader, NULL);
    Pthread_create(&tid5, NULL, reader, NULL);
    Pthread_create(&tid6, NULL, reader, NULL);
    Pthread_create(&tid7, NULL, reader, NULL);
    Pthread_create(&tid8, NULL, reader, NULL);
    Pthread_create(&tid1, NULL, writer, NULL);
    Pthread_exit(NULL);
}
