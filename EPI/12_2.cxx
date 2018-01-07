#include <iostream>
#include <unordered_map>
#include <string>

bool is_letter_constructible_from_magazine(const std::string& letter_text, 
										   const std::string& magazine_text)
{
	std::unordered_map<char, int> map;
	for (auto item : letter_text)
		++map[item];

	for (auto item : magazine_text) {
		auto it = map.find(item);
		if (it != map.cend()) {
			--it->second;
			if (it->second == 0) {
				map.erase(it);
			}
		}
	}
	return map.empty() ? true : false;
}

int main()
{
	std::string l = "abcdef";
	std::string m = "abbffecxdd";
	std::cout << std::boolalpha << is_letter_constructible_from_magazine(l, m) << std::endl;
	l = "xyzabc";
	m = "xxyyzzadcc";
	std::cout << std::boolalpha << is_letter_constructible_from_magazine(l, m) << std::endl;
}