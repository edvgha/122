#include <iostream>
#include <vector>
#include <tuple>

std::tuple<int, int> find_duplicate_missing(const std::vector<int>& arr)
{
	int n = arr.size();
	int M = (n * (n - 1)) >> 1;
	int N = 0;
	for (auto item : arr) 
		N += item;

	int diff = 0;
	if (M > N) {
		diff = M - N;
	} else {
		diff = N - M;
	}

	for (size_t i = 0; i < n; ++i) {
		if ((i + diff) < n && arr[i] == arr[i + diff]) {
			return {arr[i], M + arr[i] - N};
		}
	}
	return {-1, -1};
}

int main()
{
	auto t = find_duplicate_missing({0, 1, 2, 3, 4, 5});
	std::cout << "duplicate: " << std::get<0>(t) << " missing: " << std::get<1>(t) << std::endl;
}