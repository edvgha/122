#include "csapp.h"

typedef struct {
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    int clientfd[FD_SETSIZE];
    rio_t clientrio[FD_SETSIZE];
} pool;

void init_pool(int listenfd, pool* p);
void add_client(int connfd, pool* p);
void check_client(pool* p);


int byte_count = 0;

void init_pool(int listenfd, pool* p)
{
    int i;
    p->maxi = -1;
    for (i = 0; i < FD_SETSIZE; ++i) 
        p->clientfd[i] = -1;

    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool* p)
{
    int i;
    p->nready--;
    /* Find an available slot */
    for (i = 0; i < FD_SETSIZE; ++i) {
        if (p->clientfd[i] < 0) {
            /* Add connected descriptor to the pool */
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);

            /* Add the descriptor to descriptor set */
            FD_SET(connfd, &p->read_set);

            /* Update max descriptor and pool highwater mark */
            if (connfd > p->maxfd)
                p->maxfd = connfd;
            if (i > p->maxi)
                p->maxi = i;
            break;
        }
    }
    if (i == FD_SETSIZE) /* No empty slot */
        app_error("add_client error: Too many clients");
}

void check_client(pool* p)
{
    int i , connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for (i = 0; (i <= p->maxi) && (p->nready > 0); ++i) {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))) {
            p->nready--;
            if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
                if (n == MAXLINE - 1) {
                    printf("Kill client ....\n");
                    Close (connfd);
                    FD_CLR(connfd, &p->read_set);
                    p->clientfd[i] = -1;
                } else {
                    printf("read fd : %d nread %d\n", connfd, n);
                    byte_count += n;
                    printf("Server received %d (%d totoal) bytes on fd %d\n", n, byte_count, connfd);
                    Rio_writen(connfd, buf, n);
                }
            } else {
                printf("close fd : %d\n", connfd);
                Close (connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}

int main(int argc, char** argv)
{
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    static pool pool;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
    }
    port = atoi(argv[1]);
    listenfd = Open_listenfd(port);
    init_pool(listenfd, &pool);
    while (1) {
        printf("Iter .... \n");
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);
        printf("Iter progress %d events .... \n", pool.nready);

        if (FD_ISSET(listenfd, &pool.ready_set)) {
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            printf("Add client %d .... \n", connfd);
            add_client(connfd, &pool);
        }

        check_client(&pool);
    }
}
