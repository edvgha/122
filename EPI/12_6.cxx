#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

std::pair<int, int> find_smallest_subarray_covering_set(std::vector<std::string>& paragraph, 
														std::unordered_set<std::string>& keywords)
{
	std::unordered_map<std::string, int> keywords_to_cover;
	for (auto item : keywords)
		++keywords_to_cover[item];

	std::pair<int, int> r = {-1, -1};
	int remaining_to_cover = keywords.size();

	for (int left = 0, right = 0; right < paragraph.size(); ++right) {
		if (keywords.count(paragraph[right]) && --keywords_to_cover[paragraph[right]] >= 0)
			--remaining_to_cover;

		while (remaining_to_cover == 0) {
			if ((r.first == -1 && r.second ==  -1) || (r.second - r.first > right - left)) {
				r = {left, right};
			}
			if (keywords.count(paragraph[left]) && ++keywords_to_cover[paragraph[left]] > 0) {
				++remaining_to_cover;
			}
			++left;
		}
	}
	return r;
}


int main()
{
	std::vector<std::string> paragraph = {"apple", "banana", "apple", "apple", "dog", "cat", "apple", "dog", "banana", "apple", "cat", "dog"};
	std::unordered_set<std::string> keywords = {"banana", "cat"};

	std::pair<int, int> r = find_smallest_subarray_covering_set(paragraph, keywords);
	std::cout << "(" << r.first << ", " << r.second << ")" << std::endl;
}