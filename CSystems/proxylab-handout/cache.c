#include "cache.h"
#include <assert.h>

void node_read_data(struct node_t* n, int sockfd);
void cache_rm_back(struct cache_t* l);
void cache_push_front(struct cache_t* l, struct node_t* n);
void cache_pop(struct cache_t* l, struct node_t* n);
void cache_move_front(struct cache_t* l, struct node_t* n);
void display(struct cache_t* l);

struct node_t* node(char* host, char* port, char* resource, void* data, size_t ndata)
{
    printf("%s %lu %s %lu %s %lu\n", host, strlen(host), port, strlen(port), resource, strlen(resource));
    struct node_t* n = Malloc(sizeof(struct node_t));

    n->host = Malloc(sizeof(char) * (strlen(host) + 1));
    strncpy(n->host, host, strlen(host) + 1);
    printf("%s %lu %s %lu\n", n->host, strlen(n->host), host, strlen(host));

    n->port = Malloc(sizeof(char) * (strlen(port) + 1));
    strncpy(n->port, port, strlen(port) + 1);
    printf("%s %lu %s %lu\n", n->port, strlen(n->port), port, strlen(port));

    n->resource = Malloc(sizeof(char) * (strlen(resource) + 1));
    strncpy(n->resource, resource, strlen(resource) + 1);
    printf("%s %lu %s %lu\n", n->resource, strlen(n->resource), resource, strlen(resource));

    n->data = Malloc(ndata);
    memcpy(n->data, data, ndata);

    n->ndata = ndata;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void node_free(struct node_t* n)
{
    Free(n->resource);
    Free(n->port);
    Free(n->host);
    Free(n->data);
    Free(n);
}

void cache_init(struct cache_t* l)
{
    l->head = l->tail = NULL;
    l->size = 0;
    Sem_init(&l->mutex, 0, 1);
}

void node_read_data(struct node_t* n, int sockfd)
{
    Rio_writen(sockfd, n->data, n->ndata);
}

int cache_read(struct cache_t* l, char* host, char* port, char* resource, int sockfd)
{
    P(&l->mutex);
    display(l);
    struct node_t* n = l->head;
    int success = 0;
    while (n != NULL) {
        if (!strcasecmp(host, n->host) &&
            !strcasecmp(port, n->port) &&
            !strcasecmp(resource, n->resource)) {
            node_read_data(n, sockfd);
            cache_move_front(l, n);
            success = 1;
            break ;
        }
        n = n -> next;
    }
    V(&l->mutex);
    return success;
}

void cache_write(struct cache_t* l, char* host, char* port, char* resource, void* data, int ndata)
{
    P(&l->mutex);
    assert(l);
    struct node_t* n = l->head;
    int success = 0;
    while (n != NULL) {
        if (!strcasecmp(host, n->host) &&
            !strcasecmp(port, n->port) &&
            !strcasecmp(resource, n->resource)) {
            success = 1;
            break ;
        }
        n = n -> next;
    }
    if (success) {
        V(&l->mutex);
        return ;
    }
    if (ndata > MAX_OBJECT_SIZE) {
        V(&l->mutex);
        return ;
    }
    while ((l->size + ndata) > MAX_CACHE_SIZE) {
        cache_rm_back(l);
    }
    n = node(host, port, resource, data, ndata);
    cache_push_front(l, n);
    V(&l->mutex);
}

void cache_rm_back(struct cache_t* l)
{
    if (!l->tail) {
        return ;
    }
    l->size -= l->tail->ndata;
    if (l->tail->prev) {
        struct node_t* n = l->tail->prev;
        n->next = NULL;
        l->tail->prev = NULL;
        Free(l->tail);
        l->tail = n;
    } else {
        Free(l->tail);
        l->head = l->tail = NULL;
    }
}

void cache_push_front(struct cache_t* l, struct node_t* n)
{
    n->next = l->head;
    n->prev = NULL;
    if (l->head)
        l->head->prev = n;
    l->head = n;
    l->size += n->ndata;
}

void cache_pop(struct cache_t* l, struct node_t* n)
{
    l->size -= n->ndata;
    if (l->head == n) {
        if (n->next) {
            l->head = n->next;
            n->next->prev = NULL;
            n->next = NULL;
            return ;
        } else {
            l->head = l->tail = NULL;
        }
    } else if (l->tail == n) {
        if (n->prev) {
            l->tail = n->prev;
            n->prev->next = NULL;
            n->prev = NULL;
        } else {
            l->head = l->tail = NULL;
        }
    } else {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        n->prev = NULL;
        n->next = NULL;
    }
}

void cache_move_front(struct cache_t* l, struct node_t* n)
{
    if (l->head == n) {
        return ;
    }
    cache_pop(l, n);
    cache_push_front(l, n);
}

void display(struct cache_t* l)
{
    printf("-----------------\n");
    struct node_t* n = l->head;
    while (n != NULL) {
        printf("%s %lu\n", n->host, strlen(n->host));
        printf("%s %lu\n", n->port, strlen(n->port));
        printf("%s %lu\n", n->resource, strlen(n->resource));
        printf("%lu\n", n->ndata);
        n = n->next;
    }
    printf("-----------------\n");
}
