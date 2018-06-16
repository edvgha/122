#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void uniquiefy(std::vector<std::pair<std::string, std::string>>& arr)
{
    std::sort(arr.begin(), arr.end(), [](std::pair<std::string, std::string> a, std::pair<std::string, std::string> b) { return a.first < b.first; });
    size_t last_unique_id = 0;
    for (size_t i = 0; i < arr.size(); ++i) 
    {
        if (arr[i].first == arr[last_unique_id].first)
            continue;
        std::swap(arr[i], arr[++last_unique_id]);
    }

    ++last_unique_id;
    std::cout << last_unique_id << " " << arr.size() << std::endl;
    for (size_t i = 0; i < last_unique_id; ++i)
        std::cout << "[" << arr[i].first << ", " << arr[i].second << "]\n";
    std::cout << std::endl;
}

int main()
{
    //std::vector<std::pair<std::string, std::string>> arr = {{"Ian", "Bell"}, {"David", "Gower"}, {"David", "Gower"}, {"Ian", "Botham"}, {"Jone", "Smith"}, {"Mike", "Mike"}};
    std::vector<std::pair<std::string, std::string>> arr = {{"a", "a"}, {"c", "c"}, {"c", "c"}, {"d", "d"}, {"e", "e"}, {"d", "d"}, {"i", "i"}};
    uniquiefy(arr);
}
