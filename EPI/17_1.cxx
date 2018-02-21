#include <vector>
#include <algorithm>
#include <iostream>

std::vector<std::pair<int, int>> optimum_task_assignment(std::vector<int> taskDurations)
{
	std::sort(taskDurations.begin(), taskDurations.end());
	size_t n = taskDurations.size();
	std::vector<std::pair<int, int>> optimumAssignment;
	for (size_t i = 0, j = n - 1; i < j; ++i, --j) {
		optimumAssignment.emplace_back(std::pair<int, int>({taskDurations[i], taskDurations[j]}));
	}
	return optimumAssignment;
}

int main()
{
	auto r = optimum_task_assignment({5, 2, 1, 6, 4, 4});
	for (size_t i = 0; i < r.size(); ++i) 
		std::cout << r[i].first << " - " << r[i].second << std::endl;
}