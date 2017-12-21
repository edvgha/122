#include <iostream>
#include <string>
#include <memory>

int main()
{
	std::unique_ptr<std::string> u_ptr = std::make_unique<std::string>("hello world");
	//auto ptr = u_ptr.get();
	std::cout << *u_ptr << std::endl;
	auto ptr = u_ptr.release();
	std::cout << *ptr << std::endl;
	delete ptr;
}
