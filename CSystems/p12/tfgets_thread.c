#include "csapp.h"

sem_t w;

struct args {
    FILE* stream;
    int size;
    char* cstr;
    sem_t mutex;
};

void* thread1(void* vargp)
{
    Pthread_detach(Pthread_self());
    Sleep(5);
    struct args* a = vargp;
    P(&w);
    a->cstr = NULL;
    V(&(a->mutex));
    //V(&w);
    Pthread_exit(NULL);
}

void* thread2(void* vargp)
{
    Pthread_detach(Pthread_self());
    struct args* a = vargp;
    char* x = Fgets(a->cstr, a->size, a->stream);
    P(&w);
    a->cstr = x;
    //V(&w);
    V(&(a->mutex));
    Pthread_exit(NULL);
}

char* tfgets(char* s, int size, FILE* stream)
{
    Sem_init(&w, 0, 1);
    struct args vargp;
    Sem_init(&vargp.mutex, 0, 1);
    P(&vargp.mutex);

    vargp.stream = stream;
    vargp.size = size;
    vargp.cstr = s;

    pthread_t tid1, tid2;

    Pthread_create(&tid1, NULL, thread1, &vargp);
    Pthread_create(&tid2, NULL, thread2, &vargp);

    P(&vargp.mutex);
    return vargp.cstr;
}
