#include <iostream>
#include "util.hpp"

uint64_t swap(uint64_t d, uint8_t i, uint8_t j)
{
    uint8_t ithBit = (d >> i) & 0x1;
    uint8_t jthBit = (d >> j) & 0x1;

    if (0 == (((d >> i) & 0x1) ^ ((d >> j) & 0x1)))
        return d;

    return d ^ ((static_cast<uint64_t>(1) << i) | (static_cast<uint64_t>(1) << j));
}

int main(int argc, char const *argv[])
{
    uint64_t d = 0x7affbaabcd85ff95;
    printBinary(d);
    //printBinary(swap(d, 62, 1));
    printBinary(swap(d, 2, 1));
	return 0;
}
