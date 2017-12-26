#include <iostream>
#include <vector>

int search_occurrence(const std::vector<int>& arr, int k)
{
	int result;
	int left = 0;
	int right = arr.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] > k) {
			right = mid - 1;
		} else if (arr[mid] == k) {
			result = mid;
			right = right - 1;
		} else {
			left = mid + 1;
		}
	}
	return result;
}

int main()
{
	std::cout << search_occurrence({-14, -10, 2, 108, 108, 243, 285, 285, 285, 401}, 285) << std::endl;
}