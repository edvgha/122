#include "csapp.h"
#define MAXARGS   128

int mysystem(char* command)
{
    char *argv[MAXARGS]; 
    argv[0] = "/bin/sh";
    argv[1] = "-c";
    argv[2] = command;
    int status;

    pid_t pid;
    if ((pid = Fork()) == 0) {
        if (execve("/bin/sh", argv, environ) < 0) {
            printf("%s: Command not found.\n", argv[0]);
            exit(0);
        }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return status;
}

int main()
{
    int r = mysystem("exit 3");
    printf("return %d\n", r);
}
