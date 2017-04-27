#include "csapp.h"
#define N 2

int main() 
{
    int status, i;
    pid_t pid;

    /* Parent creates N children */
    for (i = 0; i < N; i++)                   
        if ((pid = Fork()) == 0) { /* child */  
            int a[4];
            a[7] = 99;
            printf("CHILD r %d\n", a[11]);
 //           exit(0);
        }

    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status))                
            printf("child %d terminated normally with exit status=%d\n",
                    pid, WEXITSTATUS(status)); 
        if (WIFSIGNALED(status))
            printf("valod child %d sig number %d\n", pid, WTERMSIG(status));
        else
            printf("child %d terminated abnormally\n", pid);
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)
        unix_error("waitpid error");

    exit(0);
}
