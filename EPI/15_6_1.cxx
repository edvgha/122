#include <iostream>
#include <vector>
#include <string>

using vector = std::vector<std::string>;

void match_parens_internal(int l, int r, int total, vector vec)
{
    if (0 == total)
    {
        for (auto el : vec)
            std::cout << el;
        std::cout << std::endl;
    }
    //std::cout << "LEFT " << l << " " << r << " " << total << std::endl;
    if (l > 0)
    {
        vector vec1 = vec;
        vec1.push_back("(");
        match_parens_internal(l - 1, r + 1, total - 1, vec1);
    }

    //std::cout << "RIGHT " << l << " " << r << " " << total << std::endl;
    if (r > 0)
    {
        vector vec2 = vec;
        vec2.push_back(")");
        match_parens_internal(l, r - 1 , total - 1, vec2);
    }
}

int main()
{
    vector vec;
    match_parens_internal(4, 0, 8, vec);
}
