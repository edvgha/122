#include <iostream>
#include <vector>
#include <limits>

std::pair<int, int> max_profit1(std::vector<int>& arr)
{
    int min_so_far = std::numeric_limits<int>::max();
    int max_profit = 0;
    for (size_t i = 0; i < arr.size(); ++i)
    {
        int profit = arr[i] - min_so_far;
        max_profit = std::max(max_profit, profit);
        min_so_far = std::min(arr[i], min_so_far);
    }
    return {min_so_far, max_profit};
}

int main()
{
    std::vector<int> arr = {310, 315, 275, 295, 260, 270, 290, 230, 255, 250};
    //std::vector<int> arr = {10, 50, 5, 40, 20, 60, 0};
    auto [min, max] = max_profit1(arr);
    std::cout << "[" << min << ", " << max << "]" << std::endl;
}
