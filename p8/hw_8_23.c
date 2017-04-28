#include "csapp.h"

int counter = 0;

void handler(int sig)
{
    counter++;
    sleep(1);
    return;
}

int main()
{
    int i;

    if (Signal(SIGUSR2, handler) == SIG_ERR)
        unix_error("signal error");

    if (Fork() == 0) {
        for (i = 0; i < 5; i++) {
            Kill(getppid(), SIGUSR2);
            printf("sent SIGUSR2 to parent\n");
        }
        exit(0);
    }

    Wait(NULL);
    printf("counter=%d\n", counter);
    exit(0);
}
