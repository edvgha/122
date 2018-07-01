#include <iostream>
#include <vector>

std::vector<int> cache;

int steps_k_n(int k, int n)
{
    if (k == n)
    {
        return (1 << (n - 1));
    }
    if (n == 1)
    {
        return 1;
    }

    int res = 0;
    for (int i = 1; i <= k; ++i)
    {
        if (n - i > 0) 
        {
            if (cache[n - i] == -1)
            {
                printf("MISS\n");
                cache[n - i] = steps_k_n(k, n - i);
            } 
            else 
            {
                printf("HIT\n");
            }
            res += cache[n - i];
        }
    }
    return res;
}

int main()
{
    cache = std::vector<int>(9, -1);
    std::cout << steps_k_n(3, 9) << std::endl;
}
