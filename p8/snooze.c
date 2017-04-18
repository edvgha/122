#include <unistd.h>
#include <stdio.h>

unsigned int snooze(unsigned int secs)
{
    unsigned int r = sleep(secs);
    printf("Slept for %u of %u secs.\n", secs - r , secs);
    return r;
}

int main()
{
    snooze(1);
}
