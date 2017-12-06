#include <iostream>
#include <array>

std::array<uint8_t, 65536> kPreComputedParity;

uint8_t parity16(uint16_t d) 
{
	uint8_t r = 1;
	while (d != 0) {
		d &= (d - 1);
		r ^= 1;
	}
	return r;
}

void preComputeParity()
{
	for (uint32_t i = 0; i < 65536; ++i) {
		kPreComputedParity[i] = parity16(i);
	}
}

/**
 * true - odd
 * false - even
 */
bool parityCheck(uint64_t d) 
{
	return kPreComputedParity[d & 0xffff] ^ kPreComputedParity[(d >> 16) & 0xffff] ^
		   kPreComputedParity[(d >> 32) & 0xffff] ^ kPreComputedParity[(d >> 48) & 0xffff];
}

int main()
{
	preComputeParity();
	std::cout << std::boolalpha << parityCheck(0x7fffffffffffffff) << '\t' 
								<< parityCheck(0) << '\t' 
								<< parityCheck(1) << '\t'
								<< parityCheck(0xffffffffffffffff) << std::endl;
}