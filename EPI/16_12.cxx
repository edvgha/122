#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int longest_nondecreasing_subsequence_length(const std::vector<int>& arr)
{
	std::vector<int> lenght(arr.size(), -1);
	lenght[0] = 1;

	for (size_t i = 1; i < arr.size(); ++i) {
		int max_id = 0;
		for (size_t j = 0; j < i; ++j) {
			if (arr[j] > arr[i]) 
				continue;
			assert(arr[j] <= arr[i]);
			if (lenght[max_id] <= lenght[j])
				max_id = j;
		}
		lenght[i] = lenght[max_id] + 1;
	}

	for (auto el : lenght) {
		std::cout << el << ' ';
	}
	std::cout << std::endl;
	return *std::max_element(lenght.begin(), lenght.end());
}

int main()
{
	std::vector<int> arr = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9};
	std::cout << longest_nondecreasing_subsequence_length(arr) << std::endl;
}