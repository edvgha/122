#include <iostream>
#include <vector>

bool search_in_2d(const std::vector<std::vector<int>>& arr2d, int k)
{
	int row = 0;
	int column = arr2d[0].size() - 1;

	while (column >= 0 && row < arr2d.size()) {
		if (arr2d[row][column] == k) {
			return true;
		} else if (arr2d[row][column] < k) {
			++row;
		} else {
			--column;
		}
	}
	return false;
}

int main()
{
	std::vector<std::vector<int>> arr2d = 
					{{-1, 2, 4, 4, 6}, 
					{1, 5, 5, 9, 21}, 
					{3, 6, 6, 9, 22}, 
					{3, 6, 8, 10, 24}, 
					{6, 8, 9, 12, 25}, 
					{8, 10, 12, 13, 40}};
	std::cout << std::boolalpha << search_in_2d(arr2d, 40) << std::endl;
}