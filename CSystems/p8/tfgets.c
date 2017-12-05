#include "csapp.h"

sigjmp_buf buf;

void handler(int sig)
{
    siglongjmp(buf, 1);
}

char* tFgets(char *ptr, int n, FILE *stream) 
{
    if (Signal(SIGUSR1, handler) == SIG_ERR)
        unix_error("signal error");
    sigsetjmp(buf, 1);
    if (Fork() == 0) {
        Sleep(5);
        Kill(getppid(), SIGUSR1);
        exit(0);
    }

    if (sigsetjmp(buf, 1)) {
        return NULL;
    } else {
        return Fgets(ptr, n, stream);
    }
}

int main()
{
    char str[20];
    char* s = tFgets(str, 20, stdin);
    if (s != NULL) 
        printf("%s\n", s);
}
