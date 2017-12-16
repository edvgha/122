#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

void reverseWords(std::string& sentence)
{
    std::reverse(sentence.begin(), sentence.end());
    bool t = false;
    int n = sentence.size();
    int s = 0;
    int e = 0;
    for (size_t i = 0; i < n; ++i) {
        if (std::isspace(sentence[i])) {
            e = i;
            std::reverse(sentence.begin() + s, sentence.begin() + e);
            s = e + 1;
            t = true;
        }
    }
    if (!std::isspace(sentence[n - 1]) && t)
        std::reverse(sentence.begin() + s, sentence.end());
}

int main()
{
    {
        std::string sentence = "Alice like Bob ";
        std::cout << sentence << ' ' << sentence.size() << std::endl;
        reverseWords(sentence);
        std::cout << sentence << ' ' << sentence.size() << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
    {
        std::string sentence = "abcdefghkl ";
        std::cout << sentence << ' ' << sentence.size() << std::endl;
        reverseWords(sentence);
        std::cout << sentence << ' ' << sentence.size() << std::endl;
    }
}
