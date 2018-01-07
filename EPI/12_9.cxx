#include <iostream>
#include <unordered_set>
#include <vector>

int longest_contained_range(const std::vector<int>& a)
{
	std::unordered_set<int> hash_table(a.begin(), a.end());
	int max = 1;

	for (auto el : a) {
		if (hash_table.count(el) == 0)
			continue;

		auto right = el;
		auto left = el;
		//move right
		while (hash_table.count(right) != 0) {
			++right;
		}
		//move left
		while (hash_table.count(left) != 0) {
			--left;
		}

		for (int i = left + 1; i < right; ++i) 
			hash_table.erase(i);

		if (max < (right - left - 1))
			max = right - left - 1;
	}
	return max;
}

int main()
{
	std::vector<int> a = {3, -2, 7, 9, 8, 1, 2, 0, -1, 5, 8};
	std::cout << longest_contained_range(a) << std::endl;
	a = {10, 5, 3, 11, 6, 100, 4};
	std::cout << longest_contained_range(a) << std::endl;
}