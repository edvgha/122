#include "csapp.h"

int main(int argc, char* argv[], char* envp[])
{
    pid_t pid;
    if ((pid = Fork()) == 0) {   /* Child runs user job */
        if (execve("/bin/ls", argv, envp) < 0) {
            printf("%s: Command not found.\n", argv[0]);
            exit(0);
        }
    } else {
        int status;
        if (waitpid(pid, &status, 0) < 0)
            unix_error("waitfg: waitpid error");
    }
}
