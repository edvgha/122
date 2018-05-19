#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> v {1, 2, 3, 2, 5, 2, 6, 2, 4, 8};
    const auto new_end (std::remove(std::begin(v), std::end(v), 2));
    v.erase(new_end, end(v));
    for (auto i : v)
        std::cout << i << ", ";
    std::cout << std::endl;

    const auto odd ([] (int i) { return i % 2 != 0; });

    v.erase(std::remove_if(std::begin(v), std::end(v), odd), std::end(v));
    v.shrink_to_fit();

    for (auto i : v)
        std::cout << i << ", ";
    std::cout << std::endl;

}
