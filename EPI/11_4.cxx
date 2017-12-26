#include <iostream>

int integer_square_root(int y)
{
	int left = 0; 
	int right = y;
	int r;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (mid * mid <= y) {
			r = mid;
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return r;
}

int main()
{
	std::cout << integer_square_root(16) << std::endl;
	std::cout << integer_square_root(300) << std::endl;
}