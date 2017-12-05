#include "csapp.h"

sigjmp_buf buf;

void handler(int sig)
{
    siglongjmp(buf, 122);
}

char* tfgets(char* s, int size, FILE* stream)
{
    pid_t pid;
    fd_set read_set;

    if (Signal(SIGUSR1, handler) == SIG_ERR)
        unix_error("signal error");
    sigsetjmp(buf, 1);

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);

    if ((pid = Fork()) == 0) {
        Sleep(5);
        Kill(getppid(), SIGUSR1);
        exit(0);
    } else {
        if (122 == sigsetjmp(buf, 1))
            return NULL;
        Select(STDIN_FILENO + 1, &read_set, NULL, NULL, NULL);
        if (FD_ISSET(STDIN_FILENO, &read_set)) {
            char* x = Fgets(s, size, stream);
            Kill(pid, SIGKILL);
            return x;
        }
    }
}

