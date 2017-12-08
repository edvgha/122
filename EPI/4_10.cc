#include <iostream>
#include <random>
#include <cassert>
/**
 * Generate random number between [a, b] 
 * if we have only generator that produces 
 * zero or one with equal probability
 */
uint8_t gen01()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    return dis(gen);
}

uint32_t genUInt()
{
    uint32_t r = 0;
    for (size_t i = 0; i < 32; ++i) {
        r += (static_cast<uint32_t>(1) << i) * gen01();
    }
    return r;
}

int random_gen(int a, int b)
{
    assert(a <= b);
    uint32_t x = genUInt();
    return a + std::floor((static_cast<uint64_t>(x) * (b - a + 1)) / static_cast<double>(4294967296));
}

int main()
{
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 30; ++j) {
            //std::cout << random_gen(10, 50) << ' ';
            //std::cout << random_gen(0, 1) << ' ';
            //std::cout << random_gen(-10, 10) << ' ';
            std::cout << random_gen(-1, 1) << ' ';
        }
        std::cout << '\n';
    }
}
