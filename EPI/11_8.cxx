#include <iostream>
#include <vector>
#include <algorithm>

int nth_element(std::vector<int>& arr, int n)
{
    int start = 0;
    int end = arr.size();

    while (true) {
        int pivot_id = (end + start) >> 1;
        int i = start;
        while (i < end)
        {
            if (i < pivot_id && arr[i] > arr[pivot_id])
            {
                if (pivot_id != i - 1)
                {
                    std::swap(arr[pivot_id - 1], arr[i]);
                }
                std::swap(arr[pivot_id], arr[pivot_id - 1]);
                --pivot_id;
                continue;
            } 
            else if (i > pivot_id && arr[i] < arr[pivot_id])
            {
                if (pivot_id != i + 1)
                {
                    std::swap(arr[pivot_id + 1], arr[i]);
                }
                std::swap(arr[pivot_id], arr[pivot_id + 1]);
                ++pivot_id;
                continue;
            }
            ++i;
        }

        if (pivot_id == n)
            return arr[n];
        else if (pivot_id > n)
            end = pivot_id;
        else if (pivot_id < n)
            start = pivot_id + 1;
    }
}

int main()
{
    std::vector<int> arr1 = {85, 27, 19, 6, 59, 63, 51, 7, 20, 18, 38, 73, 88, 39, 15, 50, 2, 30, 94, 10, 68, 14};
    std::vector<int> arr2 = {85, 27, 19, 6, 59, 63, 51, 7, 20, 18, 38, 73, 88, 39, 15, 50, 2, 30, 94, 10, 68, 14};
    int n;
    while (std::cin >> n) {
        std::nth_element(arr1.begin(), arr1.begin() + n, arr1.end());
        auto r = nth_element(arr2, n);
        std::cout << arr1[n] << std::endl;
        std::cout << r << std::endl;
    }
}
