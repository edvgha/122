#include "csapp.h"

int writable = 0;

int writecnt;
sem_t mutex, w;

void* reader(void* vargp)
{
    while(1) {
        P(&mutex);
        if (writecnt > 0) {
            V(&mutex);
        } else {
            V(&mutex);
            P(&w);

            printf("Read : %d\n", writable);
            Sleep(1);

            V(&w);
        }
    }
}

void* writer(void* vargp)
{
    while(1) {
        P(&mutex);
        writecnt++;
        if (writecnt == 1)
            P(&w);
        V(&mutex);

        printf("Write : %d\n", ++writable);
        Sleep(1);

        P(&mutex);
        writecnt--;
        if (writecnt == 0)
            V(&w);
        V(&mutex);
    }
}

int main()
{
    writecnt = 0;
    Sem_init(&mutex, 0, 1);
    Sem_init(&w, 0, 1);

    pthread_t tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8;

    Pthread_create(&tid2, NULL, reader, NULL);
    //Pthread_create(&tid3, NULL, reader, NULL);
    //Pthread_create(&tid4, NULL, reader, NULL);

    Pthread_create(&tid1, NULL, writer, NULL);
    Pthread_exit(NULL);
}
