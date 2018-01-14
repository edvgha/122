#include <iostream>
#include <vector>
#include <algorithm>

void permutations( std::vector<int>& arr, int j, std::vector<std::vector<int>>& res)
{
	if (j == arr.size() - 1)
		res.push_back(arr);

	for (int i = j; i < arr.size(); ++i) {
		std::swap(arr[j], arr[i]);
		permutations(arr, j + 1, res);
		std::swap(arr[j], arr[i]);
	}

}

int main()
{
	std::vector<std::vector<int>> res;
	std::vector<int> arr = {0, 1, 2, 3};
	permutations(arr, 0, res);

	for (size_t i = 0; i < res.size(); ++i) {
		for (size_t j = 0; j < res[i].size(); ++j) {
			std::cout << res[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}