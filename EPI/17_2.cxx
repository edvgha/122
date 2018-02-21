#include <iostream>
#include <vector>
#include <algorithm>

int min_waiting_time(std::vector<int> query_time)
{
	std::sort(query_time.begin(), query_time.end());
	int n = query_time.size() - 1;
	int r = 0;
	for (size_t i = 0; i < n; ++i) {
		r += query_time[i] * (n - i);
	}
	return r;
}

int main()
{
	std::cout << min_waiting_time({2, 5, 1, 3}) << std::endl;
	std::cout << min_waiting_time({5, 2, 1, 6, 4, 4}) << std::endl;
}