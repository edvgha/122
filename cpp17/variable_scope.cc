#include <set>
#include <iostream>

int main()
{
    std::set<int> v = {1, 2, 3, 4, 5, 6};
    if (auto it(v.find(4)); it != v.end()) {
        std::cout << "found" << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
}
