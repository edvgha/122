#include <iostream>
#include <type_traits>

void foo(int x, std::true_type)
{
    std::cout << "x: " << x << " true_type" << std::endl;
}

void foo(int x, std::false_type)
{
    std::cout << "x: " << x << " false_type" << std::endl;
}

template <bool b>
void bar(int x)
{
    foo(x, typename std::bool_constant<b>::type());
}

int main()
{
    constexpr bool b = true;
    bar<b>(4);
}
