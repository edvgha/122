#include "csapp.h"

void doit()
{
    if(Fork() == 0) {
        Fork();
        printf("hello1\n");
        return;
    }
    return ;
}

int main()
{
    doit();
    printf("hello\n");
    exit(0);
}
