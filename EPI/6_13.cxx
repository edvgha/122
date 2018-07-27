#include <string>
#include <iostream>

int strStr(std::string haystack, std::string needle)
{
    if (needle.empty())
        return 0;
    if (needle.size() > haystack.size())
        return -1;

    int nn = needle.size();
    int h_hash = 0;
    int n_hash = 0;
    const int base = 26;
    int pwd = 1;
    for (int i = 0; i < nn; ++i)
    {
        pwd = i ? pwd * base : 1;
        n_hash = n_hash * base + needle[i];
        h_hash = h_hash * base + haystack[i];
    }

    for (int i = nn; i < haystack.size(); ++i)
    {
        if (n_hash == h_hash && haystack.compare(i - nn, nn, needle) == 0) {
            return i - nn;
        }

        h_hash -= haystack[i - nn] * pwd;
        h_hash = h_hash * base + haystack[i];
        std::cout << h_hash << " " << n_hash << std::endl;
    }

    if (n_hash == h_hash && haystack.compare(haystack.size() - nn, nn, needle) == 0)
    { return haystack.size() - nn; }
    return -1;
}

int main()
{
    std::cout << strStr("ell", "ll") << std::endl;
}
