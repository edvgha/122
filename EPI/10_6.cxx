#include <iostream>
#include <queue>
#include <vector>
#include <functional>

std::vector<int> extract_k_max(const std::vector<int>& max_heap, int k)
{
	if (k > max_heap.size()) return {};

	std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> pQueue([&](int a, int b) { return max_heap[a] <= max_heap[b]; });
	std::vector<int> r;
	pQueue.push(0);
	while (r.size() < k) {
		int maxId = pQueue.top();
		pQueue.pop();
		r.push_back(max_heap[maxId]);
		int idx = (maxId << 1) + 1;
		if (idx < max_heap.size())
			pQueue.push(idx);
		++idx;
		if (idx < max_heap.size())
			pQueue.push(idx);
	}
	return r;
}

int main()
{
	auto r = extract_k_max({561, 314, 401, 28, 156, 359, 271, 11, 3}, 9);
	for (auto i : r)
		std::cout << i << ' ';
	std::cout << std::endl;
}