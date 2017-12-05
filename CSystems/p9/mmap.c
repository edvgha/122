#include <unistd.h>
#include <sys/mman.h>
#include "csapp.h"

int main() 
{
    struct stat stat;
    int fd = Open("hello.txt", O_RDWR, 0);
    char* buf;
    Fstat(fd, &stat);
    buf = mmap(NULL, stat.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
    buf[0] = 'J';
    Write(fd, buf, stat.st_size);
}
