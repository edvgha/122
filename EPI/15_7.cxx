#include <string>
#include <vector>
#include <iostream>

bool is_palindrom(const std::string& str)
{
	for (size_t i = 0, j = str.size() - 1; i < j; ++i, --j) {
		if (str[i] != str[j])
			return false;
	}
	return true;
}

std::vector<std::vector<std::string>> decomposition(const std::string& str, int t)
{
	std::vector<std::vector<std::string>> res;
	if (str.size() == 0) {
		return {{}};
	}
	if (str.size() == 1) {
		return {{str}};
	}

	for (size_t i = 1; i <= str.size(); ++i) {
		if (is_palindrom(str.substr(0, i))) {
			auto w = decomposition(str.substr(i, str.size() - i), t + 1);
			for (auto& el : w)
				el.insert(el.begin(), str.substr(0, i));
			for (auto el : w)
				res.push_back(el);
		}
	}
	return res;
}

int main()
{
	auto res = decomposition("0204451881", 0);
	std::cout << "-----res-----" << std::endl;
	for (auto item1 : res) {
		for (auto item2 : item1)
			std::cout << item2 << ' ';
		std::cout << std::endl;
	}
}