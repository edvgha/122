#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<int> task(const std::vector<char>& arr)
{
    std::vector<int> r;
    std::unordered_map<char, std::pair<int, int>> table;
    size_t n = arr.size();
    for (size_t i = 0; i < n; ++i) {
        auto it = table.find(arr[i]);
        if (it == table.end()) {
            table.insert(std::make_pair(arr[i], std::make_pair(i, i)));
        } else {
            it->second.second = i;
        }
    }

    std::vector<std::pair<int, int>> range;
    range.reserve(table.size());
    for (auto it = table.begin(); it != table.end(); ++it) {
        range.push_back(it->second);
    }

    std::sort(range.begin(), range.end());

    //merge
    n = range.size();
    size_t i = 1;
    size_t j = 0;
    while (i < n) {
        if (range[j].second < range[i].first) {
            r.emplace_back(range[j].second - range[j].first + 1);
            j = i++;
        } else {
            if (range[j].second > range[i].second) {
                //r.emplace_back(arr.begin() + range[i].first, arr.begin() + range[i].second + 1);
                ++i;
            } else {
                range[j].second = range[i].second;
                ++i;
            } 
        }
    }
    r.emplace_back(range[j].second - range[j].first + 1);

    return r;
}

int main()
{
    //auto r = task({'a', 'b', 'c', 'd', 'e', 'a', 'a', 'b', 'l', 'k', 'k', 'x'});
    //auto r = task({'a', 'b', 'c', 'd', 'e', 'f', 'j', 'k', 'l', 'm', 'n', 'o'});
    auto r = task({'a', 'b', 'c', 'd', 'a', 'e', 'f', 'g', 'h', 'i', 'j', 'e'});
    for (auto el : r) {
        std::cout << el << std::endl;
    }
}
