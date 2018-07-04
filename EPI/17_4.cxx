#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <optional>

std::optional<std::tuple<int, int, int>> sum_3(std::vector<int>& arr, int n)
{
    std::sort(arr.begin(), arr.end());

    for (size_t i = 0; i < arr.size(); ++i)
    {
        int l = 0;
        int k = arr.size() - 1;
        while (l <= k)
        {
            if (arr[l] + arr[k] == n - arr[i])
            {
                return std::make_tuple(arr[i], arr[l], arr[k]);
            } 
            else if (arr[l] + arr[k] > n - arr[i])
            {
                --k;
            }
            else
            {
                ++l;
            }
        }
    }
    return {};
}

int main()
{
    int n = 21;
    std::vector<int> arr = {11, 2, 5, 7, 3};
    auto r = sum_3(arr, n);
    //auto r = sum_3(arr, 22);
    if (!r.has_value())
    {
        std::cout << "There is no solution." << std::endl;
        return 0;
    }
    std::cout << std::get<0>(r.value()) << " + " << std::get<1>(r.value()) << " + " << std::get<2>(r.value()) << " = " << n << std::endl;
}
