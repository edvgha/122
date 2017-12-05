#include <stdio.h>
#include "csapp.h"
#include "cache.h"

static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
static const char *connection_hdr = "Connection: close\r\n";
static const char *proxy_connection_hdr = "Proxy-Connection: close\r\n";
static const char *connection = "Connection:";
static const char *proxy_connection = "Proxy-Connection:";
static const char *user_agent = "User-Agent:";
static const char *host_hdr = "Host:";
static const char *content_length_hdr = "Content-length:";

struct cache_t cache;

void forward(int fd);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
int parse_uri(char* uri, char* host, char* port, char* abs_path);
int parse_host(char* buf, char* host);
void client_header(int fd, char* server_request, char* host, char* port, char* abs_path);
void forward_header_get_response(int clientfd, char* server_request, char* host, char* port, char* abs_path);
void get(ssize_t* content_length, char* buf);
void* do_work(void* vargp);

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 0;
    }

    cache_init(&cache);
    int listenfd, connfd, clientlen;
    struct sockaddr_in clientaddr;
    pthread_t tid;

    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Pthread_create(&tid, NULL, do_work, (void *) connfd);
    }
    return 0;
}

void* do_work(void* vargp)
{
    Pthread_detach(Pthread_self());
    int fd = vargp;
    forward(fd);
    Close(fd);
    return NULL;
}

void forward(int fd)
{ 
    char server_request[MAXLINE], host[MAXLINE], port[MAXLINE], abs_path[MAXLINE];
    client_header(fd, server_request, host, port, abs_path);
    if (strlen(port) == 0) {
        port[0] = '8';
        port[1] = '0';
        port[2] = '\0';
    }
    printf("HEADER %s\n", server_request);
    printf("HOST %s\n", host);
    printf("PORT %s\n", port);
    if (cache_read(&cache, host, port, abs_path, fd))
        return ;
    forward_header_get_response(fd, server_request, host, port, abs_path);
}

void client_header(int fd, char* server_request, char* host, char* port, char* abs_path)
{
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
    sscanf(buf, "%s %s %s", method, uri, version);
    if (strcasecmp(method, "GET")) {
        clienterror(fd, method, "502", "proxy error",
                "the request method is not supported (try GET)");
        return;
    }
    if (strcasecmp(version, "HTTP/1.0") &&
        strcasecmp(version, "HTTP/1.1")) {
        clienterror(fd, method, "502", "proxy error",
                "the request version is not supported (try HTTP/1.0 or HTTP/1.1)");
        return;
    }
    if (parse_uri(uri, host, port, abs_path)) {
        clienterror(fd, method, "500", "proxy error",
                "failed to parse uri");
        return ;
    }
    sprintf(server_request, "GET %s HTTP/1.0\r\n", abs_path);
    sprintf(server_request, "%s%s", server_request, user_agent_hdr);
    sprintf(server_request, "%s%s", server_request, connection_hdr);
    sprintf(server_request, "%s%s", server_request, proxy_connection_hdr);

    int host_added = 1;
    Rio_readlineb(&rio, buf, MAXLINE);
    while(strcmp(buf, "\r\n")) {
        if (!strstr(buf, connection) &&
            !strstr(buf, proxy_connection) &&
            !strstr(buf, user_agent)) {
            if (strstr(buf, host_hdr)) {
                host_added = 0;
                if (parse_host(buf, host)) {
                    clienterror(fd, method, "500", "proxy error",
                            "failed to parse header");
                    return ;
                }
            }
            sprintf(server_request, "%s%s", server_request, buf);
        }
        Rio_readlineb(&rio, buf, MAXLINE);
    }
    if (host_added) 
        sprintf(server_request, "%sHost: %s\r\n", server_request, host);
    sprintf(server_request, "%s\r\n", server_request);
}

int parse_uri(char* uri, char* host, char* port, char* abs_path)
{
    char* pos = strstr(uri, "://");
    if (!pos) {
        if (uri[0] != '/')
            return 1;
        strncpy(abs_path, uri, strlen(uri));
        return 0;
    }
    pos += 3;
    char* p1 = strstr(pos, ":");
    char* p2 = strstr(pos, "/");
    if (!p2)
        return 1;
    if (p1) {
        strncpy(host, pos, p1 - pos);
        strncpy(port, p1 + 1, p2 - p1 - 1);
        host[p1 - pos] = '\0';
        port[p2 - p1 - 1] = '\0';
    } else {
        strncpy(host, pos, p2 - pos);
        host[p2 - pos] = '\0';
    }
    pos = p2;
    int n = 0;
    char* it;
    for (n = 0, it = pos; *it != '\0'; ++it, ++n);
    if (n > MAXLINE)
        return 1;
    strncpy(abs_path, pos, n);
    abs_path[n] = '\0';
    return 0;
}

int parse_host(char* buf, char* host)
{
    for (int i = 0; i < strlen(host); ++i) {
        host[i] = ' ';
    }
    char* pos = strchr(buf, ':');
    if (!pos) 
        return 1;
    while (*(++pos) == ' ');

    int n = 0;
    char* it;
    for (n = 0, it = pos; *it != '\n' && *it != '\r' && *it != ':'; ++it, ++n);
    if (n > MAXLINE || !strncpy(host, pos, n))
        return 1;
    host[n] = '\0';
    return 0;
}

void forward_header_get_response(int clientfd, char* server_request, char* host, char* port, char* abs_path)
{
    int serverfd;
    char buf[MAXLINE];

    rio_t rio;
    serverfd = Open_clientfd(host, port);
    Rio_writen(serverfd, server_request, strlen(server_request));
    //read header
    Rio_readinitb(&rio, serverfd);
    ssize_t content_length = 0;
    while(strcmp(buf, "\r\n")) {
        Rio_readlineb(&rio, buf, MAXLINE);
        if (strstr(buf, content_length_hdr))
            get(&content_length, buf);
        Rio_writen(clientfd, buf, strlen(buf));
    }
    char body[MAXBUF];
    if (!content_length) {
        //handle error
        sprintf(body, "<html><title>Proxy Error</title>");
        sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
        sprintf(body, "%s%s: %s\r\n", body, "500", "proxy error");
        sprintf(body, "%s<p>%s: %s\r\n", body, "failed to get content lenght", "proxy server");
        sprintf(body, "%s<hr><em>The Proxy</em>\r\n", body);
        Rio_writen(clientfd, body, strlen(body));
    } else {
        int should_be_cached = (content_length < MAX_OBJECT_SIZE) ? 1 : 0;
        ssize_t n, cnt = 0;
        if (should_be_cached) {
            char data[MAX_OBJECT_SIZE];
            while (cnt < content_length) {
                n = Rio_readnb(&rio, body, MAXBUF);
                memcpy(data + cnt, body, n);
                Rio_writen(clientfd, body, n);
                cnt += n;
            }
            cache_write(&cache, host, port, abs_path, data, content_length);
        } else {
            while (cnt < content_length) {
                n = Rio_readnb(&rio, body, MAXBUF);
                Rio_writen(clientfd, body, n);
                cnt += n;
            }
        }
    }
    Close(serverfd);
}

void get(ssize_t* content_length, char* buf)
{
    char* pos = strchr(buf, ':');
    if (!pos) 
        return ;
    while (*(++pos) == ' ');

    int n = 0;
    char* it;
    char length[MAXLINE];
    for (n = 0, it = pos; *it != '\n' && *it != '\r'; ++it, ++n);
    if (n > MAXLINE || !strncpy(length, pos, n))
        return ;
    length[n] = '\0';
    *content_length = atoi(length);
}

void clienterror(int fd, char *cause, char *errnum,
        char *shortmsg, char *longmsg)
{
    char buf[MAXLINE], body[MAXBUF];

    sprintf(body, "<html><title>Proxy Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Proxy</em>\r\n", body);

    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}
