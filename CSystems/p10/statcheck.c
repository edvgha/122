#include "csapp.h"

int main (int argc, char **argv) 
{
    struct stat stat;
    char *type, *readok;

    /* $end statcheck */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        exit(0);
    }

    int fd = Open(argv[1], O_RDONLY, S_IRUSR);
    /* $begin statcheck */
    Fstat(fd, &stat);
    if (S_ISREG(stat.st_mode))     /* Determine file type */
        type = "regular";
    else if (S_ISDIR(stat.st_mode))
        type = "directory";
    else 
        type = "other";
    if ((stat.st_mode & S_IRUSR)) /* Check read access */
        readok = "yes";
    else
        readok = "no";

    Close(fd);
    printf("type: %s, read: %s\n", type, readok);
    exit(0);
}
