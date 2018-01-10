#include <iostream>
#include <type_traits>

void foo1(std::integral_constant<int, 5>::type)
{
    std::cout << "valod" << std::endl;
}

void foo1(std::integral_constant<int, 6>::type)
{
    std::cout << "murad" << std::endl;
}

template <int n>
void foo()
{
    foo1(typename std::integral_constant<int, n>::type());
}

int main()
{
    int x;
    std::cin >> x;
    foo<5>();
}
