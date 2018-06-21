#include <iostream>
#include <vector>
#include <limits>

int max_profit2(std::vector<int>& arr)
{
    std::vector<int> subarr(arr.size(), 0);
    int min_so_far = std::numeric_limits<int>::max();
    int max_profit = 0;
    for (size_t i = 0; i < arr.size(); ++i)
    {
        int profit = arr[i] - min_so_far;
        max_profit = std::max(max_profit, profit);
        min_so_far = std::min(arr[i], min_so_far);
        subarr[i] = arr[i] - min_so_far;
    }

    int size = arr.size();
    int max_so_far = 0;
    int max_profit2 = 0;
    for (int i = size - 1; i >= 1; --i)
    {
        max_profit2 = std::max(max_so_far - subarr[i] + subarr[i - 1], max_profit2);
        max_so_far = std::max(subarr[i], max_so_far);
    }
    return max_profit2;
}

int main()
{
    //std::vector<int> arr = {310, 315, 275, 295, 260, 270, 290, 230, 255, 250};
    std::vector<int> arr = {10, 50, 5, 40, 20, 60, 0};
    std::cout << max_profit2(arr) << std::endl;
}
