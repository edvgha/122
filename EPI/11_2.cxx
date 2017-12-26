#include <iostream>
#include <vector>
#include <cassert>

int search_to_equal_to_its_index(const std::vector<int>& arr)
{
	int left = 0;
	int right = arr.size();
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] > mid) {
			right = mid - 1;
		} else if (arr[mid] == mid) {
			return mid;
		} else {
			assert(arr[mid] < mid);
			left = mid + 1;
		}
	}
	return -11;
}
int main()
{
	std::cout << search_to_equal_to_its_index({-2, 0, 2, 3, 6, 7, 9}) << std::endl;
}