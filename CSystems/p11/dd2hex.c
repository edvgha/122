#include <arpa/inet.h>
#include "csapp.h"

int main(int argc, char** argv) 
{
    if (argc != 2) {
        unix_error("Usage: ./exe <32 bit unsigned hex number>");
    }

    struct in_addr addr;
    if (0 == inet_aton(argv[1], &addr)) {
        unix_error("Failed to convert dotted decimal IP to uint");
    }
    printf("0x%08x\n", addr.s_addr);
}
