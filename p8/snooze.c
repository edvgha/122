#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"

void handler(int sig)
{
    printf("Caught SIGINT\n");
    exit(0);
}

unsigned int snooze(unsigned int secs)
{
    unsigned int r = sleep(secs);
    printf("Slept for %u of %u secs.\n", secs - r , secs);
    return r;
}

int main(int argc, char* argv[])
{
    if (Signal(SIGINT, handler) == SIG_ERR)
        unix_error("signal error");

    snooze(atoi(argv[1]));
}
