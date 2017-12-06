#include <iostream>
#include "util.hpp"

int main()
{
    uint8_t d = 44;
    printBinary(d);
    uint16_t d1 = 264;
    printBinary(d1);
    uint32_t d2 = 0x7affbaab;
    printBinary(d2);
    uint64_t d3 = 0x7affbaabcd85ff95;
    printBinary(d3);
}
