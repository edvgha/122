#include <iostream>

union data {
    uint16_t i;
    unsigned char s[2];
};

int main()
{
    char str[20] = "hello world valod";
    uint32_t checksum = 0;
    for (int i = 0; i < 10; ++i) {
        union data d;
        d.s[0] = str[i];
        d.s[1] = str[i + 1];
        checksum += d.i;
    }
    std::cout << checksum << std::endl;
}
