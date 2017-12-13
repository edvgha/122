// <1, 0, 3, 2> -> <1, 2, 0, 3>
// <3, 2, 1, 0> -> <>

/*

------------
<0, 1, 2, 3>
<0, 1, 3, 2>
<0, 2, 1, 3>
<0, 2, 3, 1>
<0, 3, 1, 2>
<0, 3, 2, 1>
------------
<1, 0, 2, 3>
<1, 0, 3, 2>
<1, 2, 0, 3>
<1, 2, 3, 0>
<1, 3, 0, 2>
<1, 3, 2, 0>
------------
<2, 0, 1, 3>
<2, 0, 3, 1>
<2, 1, 0, 3>
<2, 1, 3, 0>
<2, 3, 0, 1>
<2, 3, 1, 0>
------------
<3, 0, 1, 2>
<3, 0, 2, 1>
<3, 1, 0, 2>
<3, 1, 2, 0>
<3, 2, 0, 1>
<3, 2, 1, 0>
------------

*/

#include <iostream>
#include <array>

void nextPermutation(std::array<int, 8>& arr)
{
    //print
    for (auto el : arr) {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
    using size_type = std::array<int, 8>::size_type;
    size_type n = arr.size();
    for (size_type i = 1; i < n; ++i) {
        if (arr[n - i] < arr[n - i - 1]) {
            continue;
        }
        size_type swap_id = n - i;
        for (size_type j = n - i; j < n; ++j) {
            if (arr[n - i - 1] < arr[j])
                swap_id = j;
            else 
                break;
        }
        int t = arr[n - i - 1];
        arr[n - i - 1] = arr[swap_id];
        arr[swap_id] = t;
        std::sort(arr.begin() + n - i , arr.end());
        //print
        for (auto el : arr) {
            std::cout << el << ' ';
        }
        std::cout << std::endl;
        std::cout << "----------" << std::endl;
        return ;
    }
}

int main()
{
    /*
    std::array<int, 4> arr = {0, 1, 2, 3};
    nextPermutation(arr);
    arr = {0, 1, 3, 2};
    nextPermutation(arr);
    arr = {0, 2, 1, 3};
    nextPermutation(arr);
    arr = {0, 2, 3, 1};
    nextPermutation(arr);
    arr = {0, 3, 1, 2};
    nextPermutation(arr);
    arr = {0, 3, 2, 1};
    nextPermutation(arr);
    arr = {1, 0, 2, 3};
    nextPermutation(arr);
    arr = {1, 0, 3, 2};
    nextPermutation(arr);
    arr = {1, 2, 0, 3};
    nextPermutation(arr);
    arr = {1, 2, 3, 0};
    nextPermutation(arr);
    arr = {1, 3, 0, 2};
    nextPermutation(arr);
    arr = {1, 3, 2, 0};
    nextPermutation(arr);
    arr = {2, 0, 1, 3};
    nextPermutation(arr);
    arr = {2, 0, 3, 1};
    nextPermutation(arr);
    arr = {2, 1, 0, 3};
    nextPermutation(arr);
    arr = {2, 1, 3, 0};
    nextPermutation(arr);
    arr = {2, 3, 0, 1};
    nextPermutation(arr);
    arr = {2, 3, 1, 0};
    nextPermutation(arr);
    arr = {3, 0, 1, 2};
    nextPermutation(arr);
    arr = {3, 0, 2, 1};
    nextPermutation(arr);
    arr = {3, 1, 0, 2};
    nextPermutation(arr);
    arr = {3, 1, 2, 0};
    nextPermutation(arr);
    arr = {3, 2, 0, 1};
    nextPermutation(arr);
    arr = {3, 2, 1, 0};
    nextPermutation(arr);
    */
    std::array<int, 8> arr = {5, 7, 6, 1, 0, 4, 3, 2};
    nextPermutation(arr);
}
