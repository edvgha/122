#include <iostream>
#include <string>

void printBinary16(uint16_t d)
{
	std::string s(16, 'x');
	for (uint8_t i = 0; i < 16; ++i) {
		s[15 - i] = static_cast<char>('0' + ((d >> i) & 0x1));
	}
	std::cout << s << std::endl;
}

uint16_t clearLSB(uint16_t d)
{
	return (d & (d - 1));
}

uint16_t extractLSB(uint16_t d)
{
	//not always right
	return (d & (~(d - 1)));
}

int main(int argc, char const *argv[])
{
	return 0;
}