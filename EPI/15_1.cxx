#include <iostream>
#include <vector>

void honoi(int disks, int i, int j, int l)
{
	if (0 == disks) return ;
	honoi(--disks, i, l, j);
	std::cout << "disk : " << (disks + 1) << " from " << i << " to " << l << std::endl;
	honoi(disks, j, i, l);
}

int main()
{
	honoi(19, 1, 2, 3);
}