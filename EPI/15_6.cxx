#include <iostream>
#include <unordered_set>
#include <string>

std::unordered_set<std::string> matched_parens(int n)
{
    if (0 == n)
        return std::unordered_set<std::string>();
    if (1 == n)
    {
        std::unordered_set<std::string> s = {"()"};
        return s;
    }
    std::unordered_set<std::string> s = matched_parens(n - 1);
    std::unordered_set<std::string> ss;
    for (auto el : s)
    {
        ss.insert("(" + el + ")");
        ss.insert("()" + el);
        ss.insert(el + "()");
    }
    return ss;
}

int main()
{
    auto r = matched_parens(4);
    for (auto el : r)
        std::cout << el << '\n';
    std::cout << std::endl;
}
