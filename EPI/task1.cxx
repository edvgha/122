#include <iostream>
#include <vector>

std::vector<int> a_z(26, -1);

void erase_from(int from, int to, const std::vector<char>& arr)
{
	for (int i = to; i < from; ++i) {
		a_z[arr[i] - 'a'] = -1;
	}
}

std::vector<std::vector<char>> task(const std::vector<char>& arr, size_t k)
{
	std::vector<std::vector<char>> r;
	size_t n = arr.size();
	int twice = -1;
	size_t start = 0;
	for (size_t i = 0; i < n; ++i) {
		if (a_z[arr[i] - 'a'] == -1) {
			a_z[arr[i] - 'a'] = i;
		} else {
			if (twice == -1) {
				twice = i;
			} else {
				if (arr[twice] == arr[i]) {
					//3 time
					//erase from twice to start
					erase_from(twice, start ,arr);
					a_z[arr[i] - 'a'] = twice;
					//start = twice;
                    start++;
					twice = i;
				} else {
					//2 2 time
					//erase from a_z[arr[i] - 'a'] to start
					erase_from(a_z[arr[i] - 'a'], start, arr);
					start = a_z[arr[i] - 'a'];
					twice = i;
				}
			}
		}
		if (i == start + k - 1) {
			//DONE; [start, i]
			if (twice != -1)
				r.emplace_back(arr.begin() + start, arr.begin() + i + 1);
			if (arr[twice] == arr[start]) {
				a_z[arr[start] - 'a'] = twice;
				twice = -1;
			} else {
                a_z[arr[start] - 'a'] = -1;
            }
			++start;
		}
	}
	return r;
}

int main()
{
	//auto r = task({'a', 'b', 'c', 'c', 'e', 'x', 'x', 'z', 'k'}, 5);
	auto r = task({'a', 'a', 'b', 'a', 'd', 'a', 'e', 'a', 'a'}, 5);
	for (auto el : r)  {
		for (auto e : el)
			std::cout << e << ' ';
		std::cout << std::endl;
	}
}
