#include <iostream>
/**
 * Decimal representation of integer is palindromic string?
 * true 0, 1, 7, 11, 121, 2147447412
 * false -1, 12, 100, 2147483647
 */

bool isPalindromic(int d)
{
    if (d < 0) {
        return false;
    }

    int t = d;
    int n = 1;
    while (t > 9) {
        t = t / 10;
        n *= 10;
    }
    while (d > 9) {
        if ((d % 10) != (d / n)) 
            return false;
        d = d % n;
        d /= 10;
        n /= 100;
    }
    return true;
}

int main()
{
    std::cout << std::boolalpha << isPalindromic(0) << std::endl;
    std::cout << std::boolalpha << isPalindromic(1) << std::endl;
    std::cout << std::boolalpha << isPalindromic(7) << std::endl;
    std::cout << std::boolalpha << isPalindromic(11) << std::endl;
    std::cout << std::boolalpha << isPalindromic(121) << std::endl;
    std::cout << std::boolalpha << isPalindromic(2147447412) << std::endl;

    std::cout << std::boolalpha << isPalindromic(-1) << std::endl;
    std::cout << std::boolalpha << isPalindromic(12) << std::endl;
    std::cout << std::boolalpha << isPalindromic(100) << std::endl;
    std::cout << std::boolalpha << isPalindromic(2147483647) << std::endl;
}
