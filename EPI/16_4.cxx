#include <iostream>
#include <vector>

int x_choose_y(int k, int n, std::vector<std::vector<int>>& cache)
{
	if (k == n) return 1;
	if (k == 1) return n;

	if (cache[n - 1][k - 1] != -1) {
		std::cout << "hit\n";
		return cache[n][k];
	}

	int a = x_choose_y(k, n - 1, cache);
	int b = x_choose_y(k - 1, n - 1, cache);
	cache[n - 1][k - 1] = a + b;
	return cache[n - 1][k - 1];
}

int binomial_coefficient(int k, int n)
{
	std::vector<std::vector<int>> cache(n, std::vector<int>(k, -1));
	return x_choose_y(k, n, cache);
}

int main()
{
	std::cout << binomial_coefficient(7, 22) << std::endl;
}