#include <iostream>

std::pair<int, double> foo()
{
    return std::make_pair(5, 4.4);
}

int main()
{
    auto [f, s] = foo();
    std::cout << f << " " << s << std::endl;
}
