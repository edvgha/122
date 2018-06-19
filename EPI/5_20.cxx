#include <iostream>
#include <vector>

std::vector<int> pascal_triangle(int nrows)
{
    std::vector<int> arr((nrows * (nrows + 1)) >> 1, 0);
    arr[0] = 1;
    size_t sum = 0;
    for (size_t i = 0; i < nrows - 1; ++i)
    {
        sum += (i + 1);
        arr[sum] = 1;
        arr[sum + i + 1] = 1;
        for (size_t j = 1;  j < i + 1; ++j)
        {
            arr[sum + j] = arr[sum - (i + 1) + j - 1] + arr[sum - (i + 1) + j]; 
        }
    }
    return arr;
}

int main()
{
    int nrows = 6;
    //std::vector<int> arr = {1, 1, 1, 1, 2, 1, 1, 3, 3, 1, 1, 4, 6, 4, 1};
    std::vector<int> arr = pascal_triangle(nrows);
    size_t sum = 0;
    for (size_t i = 0; i < nrows; ++i)
    {
        sum += i;
        for (size_t j = 0; j < (i + 1); ++j)
        {
            std::cout << arr[sum + j] << ' ';
        }
        std::cout << std::endl;
    }
}
