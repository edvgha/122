#include <iostream>
#include <vector>

std::vector<int> intersection(const std::vector<int>& a, const std::vector<int>& b)
{
	int i = 0;
	int j = 0;
	std::vector<int> r;
	while (i < a.size() && j < b.size()) {
		if (a[i] < b[j])
			++i;
		else if (a[i] > b[j])
			++j;
		else {
			r.push_back(a[i]);
			++i; ++j;
			while (i < a.size() && a[i - 1] == a[i]) ++i;
			while (j < b.size() && b[j - 1] == b[j]) ++j;
		}
	}
	return r;
}

int main()
{
	auto a = intersection({2, 3, 3, 5, 5, 6, 7, 7, 8, 12}, {5, 5, 6, 8, 8, 9, 10, 10});
	for (auto e : a) 
		std::cout << e << ' ';
	std::cout << std::endl;
}