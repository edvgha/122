#include <iostream>
#include <queue>
#include <vector>
#include <functional>

void median (const std::vector<int>& input)
{
	std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> max_heap([](int a, int b) { return a >= b; });
	std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> min_heap([](int a, int b) { return a <= b; });

	if (input[0] > input[1]) {
		max_heap.push(input[0]);
		min_heap.push(input[1]);
		//std::cout << "max_heap : " << input[0] << std::endl;
		//std::cout << "min_heap : " << input[1] << std::endl;
	} else {
		max_heap.push(input[1]);
		min_heap.push(input[0]);
		//std::cout << "max_heap : " << input[1] << std::endl;
		//std::cout << "min_heap : " << input[0] << std::endl;
	}

	std::cout << "median[0] = " << input[0] << std::endl;
	std::cout << "median[1] = " << (input[0] + input[1]) / 2.0 << std::endl;

	for (size_t i = 2; i < input.size(); ++i) {
		if (max_heap.top() <= input[i]) {
			if (max_heap.size() > min_heap.size()) {
				//std::cout << "move from max to min : " << max_heap.top() << std::endl;
				min_heap.push(max_heap.top());
				max_heap.pop();
			}
			max_heap.push(input[i]);
			//std::cout << "max_heap : " << input[i] << std::endl;
		} else {
			if (min_heap.size() > max_heap.size()) {
				//std::cout << "move from min to max : " << min_heap.top() << std::endl;
				max_heap.push(min_heap.top());
				min_heap.pop();
			}
			min_heap.push(input[i]);
			//std::cout << "min_heap : " << input[i] << std::endl;
		}
		//std::cout << " >>> pair : " << max_heap.top() << " " << min_heap.top() << std::endl;
		//std::cout << " >>> size : " << max_heap.size() << " " << min_heap.size() << std::endl;
		if (max_heap.size() > min_heap.size()) {
			std::cout << "median[" << i << "] = " << max_heap.top() << std::endl;
		} else if (max_heap.size() < min_heap.size()) {
			std::cout << "median[" << i << "] = " << min_heap.top() << std::endl;
		} else {
						std::cout << "median[" << i << "] = " << ((min_heap.top()  + max_heap.top()) / 2.0) << std::endl;
		}
	}
}

int main()
{
	median({1, 0, 3, 5, 2, 0, 1});
}