#include <iostream>
#include <string>
#include <cstdlib>

std::string RLE(const std::string& input)
{
    std::string r;
    size_t cnt = 1;
    char c = input[0];
    for (size_t i = 1; i < input.size(); ++i) {
        if (input[i] == c) 
            ++cnt;
        else  {
            r += std::to_string(cnt);
            r.append(1, c);
            c = input[i];
            cnt = 1;
        }
    }
    r += std::to_string(cnt);
    r.append(1, c);
    std::cout << input << std::endl;
    std::cout << r << std::endl;
    return r;
}

std::string RLD(const std::string& input)
{
    size_t s = 0;
    size_t e = 0;
    std::string r;
    for (size_t i = 0; i < input.size(); ++i) {
        if (std::isdigit(input[i])) {
            ++e;
        } else {
            int n = std::atoi(input.substr(s, e - s + 1).c_str());
            r.append(n, input[i]);
            s = i + 1;
            e = i + 1;
        }
    }
    return r;
}

int main()
{
    {
        std::string input = "abcdefgh";
        if (input != RLD(RLE(input)))
                std::cout << "FAILED" << std::endl;
    }
    {
        std::string input = "aaaaabbcddddefggggghhhhhhhhxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
        if (input != RLD(RLE(input)))
            std::cout << "FAILED" << std::endl;
    }
}
