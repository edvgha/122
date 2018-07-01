#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

bool is_decomposition(const std::unordered_set<std::string>& dictionary, const std::string& name)
{
    std::vector<int> last_length(name.size(), -1);

    for (size_t i = 0; i < name.size(); ++i)
    {
        if (dictionary.count(name.substr(0, i + 1))) {
            last_length[i] = i + 1;
        }

        if (last_length[i] == -1) 
        {
            for (size_t j = 0; j < i; ++j) 
            {
                if (last_length[j] != -1 &&
                        dictionary.count(name.substr(j + 1, i - j)))
                {
                    last_length[i] = i - j;
                    break;
                }
            }
        }
    }

    for (size_t i = 0; i < last_length.size(); ++i)
    {
        std::cout << last_length[i] << " ";
    }
    std::cout << std::endl;
    return true;
}

int main()
{
    std::cout << std::boolalpha << is_decomposition({"a", "man", "play", "player"}, "playplayermana") << std::endl;
}
