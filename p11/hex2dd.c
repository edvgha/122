#include <arpa/inet.h>
#include "csapp.h"

int main(int argc, char** argv) 
{
    if (argc != 2) {
        unix_error("Usage: ./exe <32 bit unsigned hex number>");
    }

    struct in_addr addr;
    sscanf(argv[1], "%x", &addr.s_addr);
    const char* dotted_decimal_string = inet_ntoa(addr);
    printf("%s\n", dotted_decimal_string);
}
