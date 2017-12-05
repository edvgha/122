#include "csapp.h"

int counter = 1;

int main()
{
    if(fork() == 0) {
        counter--;
        printf("counter1 = %d\n", counter);
        exit(0);
    } else {
        printf("counter2 = %d\n", counter);
        Wait(NULL);
        printf("counter2 = %d\n", counter);
        printf("counter = %d\n", ++counter);
    }
    exit(0);
}
