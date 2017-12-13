#include <iostream>
#include <array>

//112223455556779

template <int n>
void uniqe(std::array<int, n>& arr)
{
    using size_type = typename std::array<int, n>::size_type;
    int el = arr[0];
    size_type j = 0;
    for (size_type i = 1; i < n; ++i) {
        if (arr[i] != el) {
            arr[++j] = arr[i];
            el = arr[i];
        }
    }
    for (size_type i = j + 1; i < n; ++i) {
        arr[i] = 0;
    }
    for (size_type i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    {
        std::array<int, 18> arr = {1, 1, 2, 2, 2, 3, 4, 5, 5, 5, 5, 6, 7, 7, 9, 10, 11, 11};
        uniqe<18>(arr);
    }
    std::cout << "------------" << std::endl;
    {
        std::array<int, 11> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        uniqe<11>(arr);
    }
}
