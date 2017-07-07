#ifndef __CACHE_H__
#define __CACHE_H__

#include "csapp.h"

#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400


struct node_t {
    char* host;
    char* port;
    char* resource;
    void* data;
    size_t ndata;
    struct node_t* next;
    struct node_t* prev;
};

struct node_t* node(char* host, char* port, char* resource, void* data, size_t ndata);
void node_free(struct node_t* n);

struct cache_t {
    struct node_t* head;
    struct node_t* tail;
    size_t size;
    sem_t mutex; 
} ;

void cache_init(struct cache_t* l);
int cache_read(struct cache_t* l, char* host, char* port, char* resource, int sockfd);
void cache_write(struct cache_t* l, char* host, char* port, char* resource, void* data, int ndata);

#endif /* __CACHE_H__ */
