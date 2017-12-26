#include <iostream>
#include <vector>

std::vector<int> almost_sorted_array(std::vector<int>& arr, int k)
{
	std::vector<int> r(arr.size(), 0);

	for (size_t i = 0; i < arr.size() - k; ++i) {
		std::sort(arr.begin() + i, arr.begin() + i + k);
		r[i] = arr[i];
	}
	for (size_t i = arr.size() - k; i < arr.size(); ++i) {
		r[i] = arr[i];
	}
	return r;
}

int main(int argc, char const *argv[])
{
	std::vector<int> v = {3, -1, 2, 6, 4, 5, 8};
	auto r = almost_sorted_array(v, 2);
	for (auto el : r)
		std::cout << el << ", ";
	std::cout << std::endl;
	return 0;
}