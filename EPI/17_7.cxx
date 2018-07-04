#include <iostream>
#include <vector>

int max_traped_water(std::vector<int>& arr)
{
    int s = 0;
    int e = arr.size() - 1;
    int max_traped_water = 0;
    while (s < e)
    {
        max_traped_water = std::max(std::min(arr[s], arr[e]) * (e - s), max_traped_water);
        if (arr[s] < arr[e])
            ++s;
        else
            --e;
    }
    return max_traped_water;
}

int main()
{
    std::vector<int> arr = {1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1};
    int max = max_traped_water(arr);
    std::cout << "max traped water = " << max << std::endl;
}

