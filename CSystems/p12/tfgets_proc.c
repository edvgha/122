#include "csapp.h"

sigjmp_buf buf;

void handler(int sig)
{
    siglongjmp(buf, 1);
}

char* tfgets(char* s, int size, FILE* stream)
{
    if (Signal(SIGUSR1, handler) == SIG_ERR)
        unix_error("signal error");
    sigsetjmp(buf, 1);
    pid_t pid;
    if ((pid = Fork()) == 0) {
        Sleep(5);
        Kill(getppid(), SIGUSR1);
        exit(0);
    } else {
    if (0 != sigsetjmp(buf, 1)) {
        return NULL;
    } else { 
        char* x = Fgets(s, size, stream);
        Kill(pid, SIGKILL);
        return x;
    }
    }
}

