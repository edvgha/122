#include "csapp.h"

int main(int argc, char** argv) 
{
    int fd;
    if (argc > 1) {
        fd = Open(argv[1], O_RDONLY, S_IRUSR);
        int r = Dup2(fd, STDIN_FILENO);
        if (r == -1 ) {
            unix_error("Dup2 error");
            return -1;
        }
    }
    int n;
    rio_t rio;
    char buf[MAXLINE];
    Rio_readinitb(&rio, STDIN_FILENO);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
        Rio_writen(STDOUT_FILENO, buf, n);

    if (argc > 1) {
        Close(fd);
    }
}
