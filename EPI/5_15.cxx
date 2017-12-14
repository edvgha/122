#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>


int genn(double a, double b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(a, b);
    return dis(gen);
}

int random(int k, int n)
{
    double f = static_cast<double>(n) / static_cast<double>(k);
    double g = genn(0, f);
    return std::floor(g);
}

void randomSubset(size_t n, size_t k)
{
    std::vector<int> w;
    for (size_t i = 0; i < n; ++i) {
        w.push_back(i);
    }
    std::vector<int> vector;
    for (size_t i = 0; i < k; ++i) {
        int x = random(k - i, n - i);
        vector.push_back(w[x]);
        w.erase(w.begin() + x);
    }
    for (auto el : vector) 
        std::cout << el << ' ';
    std::cout << std::endl;
}

int main()
{
    randomSubset(5, 3);
}
