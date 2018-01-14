#include <iostream>
#include <vector>

std::vector<int> gray_code(int nbits)
{
	if (nbits == 2) 
		return {0, 1, 3, 2};

	auto r = gray_code(nbits - 1);
	auto w = r;
	std::for_each(w.begin(), w.end() , [nbits](int& i) { i += (1 << (nbits - 1));});
	r.insert(r.end(), w.rbegin(), w.rend());
	return r;
}

int main()
{
	auto r = gray_code(4);
	for (auto el : r)
		std::cout << el << std::endl;
}