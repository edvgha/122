#include <iostream>
#include <string>

std::string snake_transform(const std::string& s)
{
    std::string top, mid, down;
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (i % 2 == 0)
            mid.push_back(s[i]);
        else if (i % 4 == 1)
            top.push_back(s[i]);
        else if (i % 4 == 3)
            down.push_back(s[i]);
    }
    return top + mid + down;
}

int main()
{
    std::string r = snake_transform("Hello_World!");
    std::cout << r << std::endl;
}
