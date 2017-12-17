#include <iostream>
#include <stack>

bool wellFormed(const std::string& input)
{
	std::stack<char> stack;
	for (auto el : input) {
		if (el == '{' || el == '[' || el == '(') {
			stack.push(el);
		}
		else if (el == '}' || el == ']' || el == ')') {
			if (stack.empty())
				return false;
			if (el == '}' && stack.top() != '{')
				return false;
			else {
				stack.pop();
				continue;
			}
			if (el == ']' && stack.top() != '[')
				return false;
			else {
				stack.pop();
				continue;
			}
			if (el == ')' && stack.top() != '(')
				return false;
			else {
				stack.pop();
				continue;
			}
		}
	}
	bool b = stack.empty() ? true : false;
	return b;
}

int main()
{
	std::cout << std::boolalpha << wellFormed("[a[b[c](x)]x]{{{ddd}}}") << std::endl;
	std::cout << std::boolalpha << wellFormed("[[[[{}{}{}{}[][]]]]()()]") << std::endl;
	std::cout << std::boolalpha << wellFormed("()()()()((())){}{[[[]]]()}") << std::endl;
	std::cout << "--------------" << std::endl;
	std::cout << std::boolalpha << wellFormed("[a[b[c](x)]x]{{ddd}}}") << std::endl;
	std::cout << std::boolalpha << wellFormed("[[[[{}{}{}{}[[]]]](()]") << std::endl;
	std::cout << std::boolalpha << wellFormed("()()()()((()){}{[[]]]()}") << std::endl;
}