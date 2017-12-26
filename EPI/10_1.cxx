#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <set>

std::vector<int> union_sorted_sets(const std::vector<std::set<int>>& sets)
{
	std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> priority_queue([](int a, int b) { return a >= b; });
	for (auto el : sets) {
		for (auto item : el) {
			priority_queue.emplace(item);
		}
	}
	std::vector<int> r(priority_queue.size(), 0);
	int i = 0;
	while (!priority_queue.empty()) {
		r[i++] = priority_queue.top();
		priority_queue.pop();
	}
	return r;
}

int main()
{
	std::vector<std::set<int>> sets = {{3, 5, 7}, {0, 6}, {0, 6, 28}};
	auto r = union_sorted_sets(sets);
	for (auto el : r) 
		std::cout << el << ' ';
}