#include <iostream>
/**
 * Reverse
 * 24 -> 42
 * -314 -> -413
 */

int reverse(int d)
{
    int r = 0;
    while (0 != d) {
        r = 10 * r + d % 10;
        d = d / 10;
    }
    return r;
}

int main()
{
    std::cout << reverse(24) << std::endl;
    std::cout << reverse(-3142) << std::endl;
}
