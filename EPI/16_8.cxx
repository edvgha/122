#include <iostream>
#include <vector>
#include <algorithm>

int min_path_weight(const std::vector<std::vector<int>>& triangle)
{
	std::vector<int> res;
	std::vector<int> res1(1, -1);
	res.push_back(triangle[0][0]);
	for (size_t i = 1; i < triangle.size(); ++i) {
		for (size_t j = 1; j < i; ++j) {
			res1[j] = std::min(res[j - 1], res[j]) + triangle[i][j];
		}
		res1[0] = res[0] + triangle[i][0];
		res1.push_back(res[i - 1] + triangle[i][i]);
		res = res1;
	}
	return *std::min_element(res.cbegin(), res.cend());
}

int main()
{
	std::vector<std::vector<int>> triangle = {{2}, {4, 4}, {8, 5, 6}, {4, 2, 6, 2}, {1, 5, 2, 3, 4}};
	std::cout << min_path_weight(triangle) << std::endl;
}