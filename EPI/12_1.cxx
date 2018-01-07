#include <iostream>
#include <unordered_set>

bool can_form_palindrom(const std::string& s)
{
	std::unordered_set<char> us;

	for (auto item : s) {
		if (us.count(item))
			us.erase(item);
		else
			us.insert(item);
	}
	return us.size() <= 1;
}

int main()
{
	std::cout << std::boolalpha << can_form_palindrom("level") << std::endl;
	std::cout << std::boolalpha << can_form_palindrom("rotator") << std::endl;
	std::cout << std::boolalpha << can_form_palindrom("foobaraboof") << std::endl;
	std::cout << std::boolalpha << can_form_palindrom("oobaraboof") << std::endl;
}