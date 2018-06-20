#include <iostream>
#include <vector>

std::pair<int, int> max_profit(std::vector<int>& arr)
{
    size_t i = 0; 
    int max = -1;
    int min = -1;
    int f_max = -1;
    int f_min = -1;
    while (i < arr.size())
    {
        if ((i == 0 || arr[i - 1] > arr[i]) && (i + 1 == arr.size() || arr[i + 1] > arr[i]))
        {
            min = arr[i];
            while (i < arr.size())
            {
                if ((i == 0 || arr[i - 1] < arr[i]) && (i + 1 == arr.size() || arr[i + 1] < arr[i]))
                {
                    max = arr[i];
                    if (max - min > f_max - f_min)
                    {
                        f_max = max;
                        f_min = min;
                        max = 0;
                        min = 0;
                        break;
                    }
                } 
                ++i;
            }
        }
        ++i;
    }
    return {f_min, f_max};
}

int main()
{
    //std::vector<int> arr = {310, 315, 275, 295, 260, 270, 290, 230, 255, 250};
    std::vector<int> arr = {11, 12, 13, 0, 100, 99, 98, 99};
    auto [min, max] = max_profit(arr);
    std::cout << "[" << min << ", " << max << "]" << std::endl;
}
