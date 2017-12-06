#include <iostream>
#include <array>
#include "util.hpp"

std::array<uint16_t, 65536> kPreComputedReverse;

void swap(uint16_t& d, uint8_t i, uint8_t j)
{
    if (0 == (((d >> i) & 0x1) ^ ((d >> j) & 0x1)))
        return ;
    d ^= ((static_cast<uint16_t>(1) << i) | (static_cast<uint16_t>(1) << j));
}

uint16_t reverse16(uint16_t d)
{
    swap(d, 0, 15);
    swap(d, 1, 14);
    swap(d, 2, 13);
    swap(d, 3, 12);
    swap(d, 4, 11);
    swap(d, 5, 10);
    swap(d, 6, 9);
    swap(d, 7, 8);
    return d;
}

void preComputeReverse()
{
    for (uint32_t i = 0; i < 65536; ++i) {
        kPreComputedReverse[i] = reverse16(i);
    }
}

uint16_t r16(uint16_t d)
{
    return kPreComputedReverse[d];
}

uint64_t reverse(uint64_t d)
{
    uint64_t r = 0;
    r = static_cast<uint64_t>(r16(d & 0xffff));
    r <<= 16;
    r |= static_cast<uint64_t>(r16((d >> 16) & 0xffff));
    r <<= 16;
    r |= static_cast<uint64_t>(r16((d >> 32) & 0xffff));
    r <<= 16;
    r |= static_cast<uint64_t>(r16((d >> 48) & 0xffff));
    return r;
}

int main(int argc, char const *argv[])
{
    preComputeReverse();
    uint64_t d = 0x7affbaabcd85ff95;
    printBinary(d);
    printBinary(reverse(d));
	return 0;
}
