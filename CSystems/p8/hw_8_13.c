#include "csapp.h"

int main()
{
    int x = 3;

    if (Fork() != 0)
        printf("x1=%d\n", ++x);

    printf("x2=%d\n", --x);
    exit(0);
}
