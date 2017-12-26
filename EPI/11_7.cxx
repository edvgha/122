#include <iostream>
#include <vector>
#include <tuple>

std::tuple<int, int> min_max(const std::vector<int>& arr)
{
	std::vector<std::tuple<int, int>> t;

	int size = (arr.size() % 2 == 0) ? arr.size() : arr.size() - 1;

	for (size_t i = 0; i < size; i += 2) {
		if (arr[i] > arr[i + 1])
			t.push_back({arr[i], arr[i + 1]});
		else 
			t.push_back({arr[i + 1], arr[i]});
	}
	if (size != arr.size()) 
		t.push_back({arr[arr.size() - 1], arr[arr.size() - 1]});

	int i = 0;
	while (i < t.size() - 1) {
		if (std::get<0>(t[i]) > std::get<0>(t[i + 1])) {
			std::get<0>(t[i + 1]) = std::get<0>(t[i]);
		}
		if (std::get<1>(t[i]) < std::get<1>(t[i + 1])) {
			std::get<1>(t[i + 1]) = std::get<1>(t[i]);
		}
		++i;
	}
	return t[t.size() - 1];
}

int main()
{
	std::vector<int> arr = {3, 2, 5, 1, 2, 4};
	std::cout << std::get<0>(min_max(arr)) << ' ' << std::get<1>(min_max(arr)) << std::endl;
}