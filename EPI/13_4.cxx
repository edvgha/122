#include <iostream>
#include <vector>
#include <algorithm>

int smallest_nonconstructible_value(std::vector<int> a)
{
	std::sort(a.begin(), a.end());

	int max_constructible = 0;
	for (int el : a) {
		if (el > max_constructible + 1)
			break;
		max_constructible += el;
	}
	return max_constructible + 1;
}

int main()
{
	std::cout << smallest_nonconstructible_value({1, 1, 1, 1, 1, 5, 10, 25}) << std::endl;
}