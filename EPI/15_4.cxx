#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> power_set(int n)
{
    if (0 == n)
        return std::vector<std::string>();

    if (1 == n)
    {
        std::vector<std::string> r(2);
        r[0] = "0";
        r[1] = "1";
        return r;
    }

    std::vector<std::string> ps = power_set(n - 1);
    std::vector<std::string> t1(ps.size());
    std::vector<std::string> t2(ps.size());
    for (size_t i = 0; i < ps.size(); ++i) 
    {
        t1[i] = "0" + ps[i];
        t2[i] = "1" + ps[i];
    }
    std::vector<std::string> result;
    result.insert(result.end(), t1.begin(), t1.end());
    result.insert(result.end(), t2.begin(), t2.end());
    return result;
}

int main()
{
    auto r = power_set(5);
    for (auto el : r)
        std::cout << el << '\n';
    std::cout << std::endl;
}
