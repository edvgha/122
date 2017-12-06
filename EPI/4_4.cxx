#include <iostream>
#include <cmath>

int closestIntWithSameWeight(int d)
{
    int lone = std::log2(static_cast<int>(d & (~(d - 1))));
    int lzero = std::log2(static_cast<int>(d & (~(d + 1))) + 1);
    if (lone > lzero) {
        return d - (1 << (lone - 1));
    } 
    return d + (1 << (lzero - 1));
}

/* int closestIntWithSameWeight(int d)
{
    size_t n = 8 * sizeof(int);
    int orig = d;
    for (size_t i = 0; i < n; ++i) {
        if (((d & 0x3) == 1) || ((d & 0x3) == 2)) {
            return orig ^ (3 << i);
        }
        d >>= 1;
    }
	return d;
}*/

int main()
{
    std::cout << closestIntWithSameWeight(12) << std::endl;
    std::cout << closestIntWithSameWeight(7) << std::endl;
	return 0;
}
