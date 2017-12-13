#include <iostream>
#include <random>
#include <vector>

int gen(int a, int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(a, b);
    return dis(gen);
}

void sampleK(size_t k)
{
    std::vector<int> samples(k);
    int d;
    unsigned n = 0;
    while (std::cin >> d) {
        if (n < k) {
            samples[n] = d;
        } else {
            if (gen(0, n - 1) < k) {
                samples[gen(0, k - 1)] = d;
            }
        }
        ++n;
        for (auto el : samples) {
            std::cout << el << ' ';
        }
        std::cout << std::endl;
    }
}

int main()
{
    size_t s;
    std::cin >> s;
    sampleK(s);
}
