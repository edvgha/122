#include <iostream>
#include <vector>
#include <unordered_map>

std::unordered_map<int, std::vector<std::vector<int>>> cache;

std::vector<std::vector<int>> combination(int final_score)
{
	if (cache.count(final_score)) {
		return cache[final_score];
	}

	//std::cout << "combination: " << final_score << std::endl;
	if (final_score < 0) 
		return {};
	if (final_score == 0)
		return {{}};

	std::vector<std::vector<int>> res;
	
	auto v_7 = combination(final_score - 7);
	if (!v_7.empty()) {
		for (auto& el : v_7) 
			el.push_back(7);
		for (auto el : v_7)
			res.push_back(el);
	}
	auto v_3 = combination(final_score - 3);
	if (!v_3.empty()) {
		for (auto& el : v_3) 
			el.push_back(3);
		for (auto el : v_3)
			res.push_back(el);
	}
	auto v_2 = combination(final_score - 2);
	if (!v_2.empty()) {
		for (auto& el : v_2)
			el.push_back(2);
		for (auto el : v_2)
			res.push_back(el);
	}
	cache[final_score] = res;
	return cache[final_score];
}

int main()
{
	std::vector<std::vector<int>> w = combination(10);
	for (auto& e1 : w) {
		for (auto& e2 : e1)
			std::cout << e2 << ' ';
		std::cout << std::endl;
	}
	std::cout << std::endl;
}