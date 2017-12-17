#include <iostream>
#include <stack>
#include <vector>

std::vector<int> sunsetView(const std::vector<int>& buildings)
{
	std::stack<int> stack;

	using size_type = std::vector<int>::size_type;
	size_type n = buildings.size();
	for (size_type i = 0; i < n; ++i) {
		while (!stack.empty() && buildings[n - 1 - i] >= stack.top()) {
			stack.pop();
		}
		stack.push(buildings[n - 1 - i]);
	}

	std::vector<int> result;
	while (! stack.empty()) {
		result.push_back(stack.top());
		stack.pop();
	}
	return result;
}

int main()
{
	std::vector<int> v = sunsetView({1, 1, 2, 2, 3, 3, 4, 4, 5});
	for (auto el : v)
		std::cout << el << ' ';
	std::cout << std::endl;
	v = sunsetView({5, 4, 4, 1, 3, 2, 1, 1, 1});
	for (auto el : v)
		std::cout << el << ' ';
	std::cout << std::endl;
	v = sunsetView({2, 2, 1, 1, 2, 3, 4, 3, 2, 1, 5, 6});
	for (auto el : v)
		std::cout << el << ' ';
	std::cout << std::endl;
	v = sunsetView({8, 2, 2, 1, 1, 2, 3, 4, 3, 2, 1, 5, 6});
	for (auto el : v)
		std::cout << el << ' ';
	std::cout << std::endl;
}