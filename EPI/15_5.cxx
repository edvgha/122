#include <iostream>
#include <vector>
#include <numeric>

std::vector<std::vector<int>> combinations(int k, int n)
{
	//std::cout << "k: " << k << " n: " << n << std::endl;
	if (k == 1) {
		std::vector<std::vector<int>> res;
		for (size_t i = 1; i < n + 1; ++i) {
			res.push_back(std::vector<int>(1, i));
		}
		return res;
	}
	if (k == n) {
		std::vector<int> v(n, 0);
		std::iota(v.begin(), v.end(), 1);
		return {v};
	}
	std::vector<std::vector<int>> res1 = combinations(k, n - 1);
	std::vector<std::vector<int>> res2 = combinations(k - 1, n - 1);
	for (auto& el : res2) {
		el.push_back(n);
	}
	res1.insert(res1.end(), res2.begin(), res2.end());
	return res1;
}

int main()
{
	auto res = combinations(3, 5);
	for (auto item1 : res) {
		for (auto item2: item1) {
			std::cout << item2 << ' ';
		}
		std::cout << std::endl;
	}
}