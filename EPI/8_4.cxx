#include <iostream>
#include <stack>
#include <string>

std::string normalizePathname(const std::string& input)
{
	std::stack<std::string> stack;
	int s = -1;
	for (int i = 0; i < input.size(); ++i) {
		if (input[i] == '/') {
			std::string str = input.substr(s + 1, i - s);
			if (str == "/" && i == 0) {
				if (stack.empty()) 
					stack.push(str);
			} else if (str == "../") {
				if (!stack.empty()) 
					stack.pop();
				else
					stack.push(str);
			} else if (str != "./" && str != "/") {
				if (!stack.empty() && stack.top() == str)
					stack.pop();
				else
					stack.push(str);
			}
			s = i;
		}
	}
	std::string result = s != input.size() - 1 ? input.substr(s + 1, input.size() - 1 - s) : "";
	while (!stack.empty()) {
		result.insert(result.begin(), stack.top().begin(), stack.top().end());
		stack.pop();
	}
	return result;
}

int main()
{
	std::cout << normalizePathname("/x/y///./../z/../y/file.txt") << std::endl;
	std::cout << normalizePathname("x/y///./../z/../y/file.txt") << std::endl;
	std::cout << normalizePathname("/x/y/z/e/file.txt") << std::endl;
	std::cout << normalizePathname("x/y/z/e/file.txt/") << std::endl;
	std::cout << normalizePathname("/x/y/z/a/b/c/.././../././../../../file.txt") << std::endl;
	std::cout << normalizePathname("x//y/z/a/b/c/.././../././../../../file.txt") << std::endl;

}