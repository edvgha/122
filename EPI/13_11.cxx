#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int find_cap(std::vector<int>& arr, int payroll)
{
    std::sort(arr.begin(), arr.end(), [](int a, int b) { return a > b; });
    int payroll_old = 0;
    for (auto el : arr)
        payroll_old += el;

    int sum = 0;
    for (size_t i = 0; i < arr.size(); ++i) 
    {
        sum += arr[i];
        if (sum < (payroll_old - payroll))
            continue;
        auto t = (sum - (payroll_old - payroll)) / (i + 1);
        if (t > arr[i + 1])
            return t;
    }
    assert(false);
    return 0;
}

int main()
{
    int payroll = 210;
    std::vector<int> arr = {90, 30, 100, 40, 20, 120, 150};
    int cap = find_cap(arr, payroll);
    std::cout << "cap : " << cap << std::endl;
}
