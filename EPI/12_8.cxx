#include <iostream>
#include <vector>
#include <unordered_map>

std::pair<size_t, size_t> max_unique_subarray(std::vector<char>& arr)
{
    std::unordered_map<char, size_t> map;
    size_t start = 0;
    size_t end = 0;
    size_t mstart = 0;
    size_t mend = 0;
    size_t i = 0;
    while (i < arr.size())
    {

        auto [it, success] = map.insert({arr[i], i});
        if (success) 
        {
            end = i++;
            if (end - start > mend - mstart)
            {
                mend = end;
                mstart = start;
            }
        } 
        else 
        {
            i = ++(it -> second);
            start = end = i;
            map.clear();
        }
    }
    return {mstart, mend};
}

int main()
{
    std::vector<char> arr = {'f', 's', 'f', 'e', 't', 'w', 'e', 'n', 'w', 'e'};
    auto [start, end] = max_unique_subarray(arr);
    std::cout << start << ' ' << end << std::endl;
}
