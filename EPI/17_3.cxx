#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> min_coverage(std::vector<std::pair<int, int>> intervals)
{
    std::vector<int> res;
    std::sort(intervals.begin(), intervals.end());
    auto [l, r] = intervals[0];
    res.push_back(r);
    for (size_t i = 1; i < intervals.size(); ++i)
    {
        auto [l1, r1] = intervals[i];
        if (r < l1)
        {
            r = r1;
            res.push_back(r);
        }
    }
    return res;
}

int main()
{
    //auto r = min_coverage({{0, 3}, {2, 6}, {3, 4}, {6, 9}});
    auto r = min_coverage({{1, 2}, {2, 3}, {3, 4}, {2, 3}, {3, 4}, {4, 5}});
    for (auto el : r)
        std::cout << el << " ";
    std::cout << std::endl;
}
