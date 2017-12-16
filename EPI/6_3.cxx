#include <iostream>
#include <string>
#include <cmath>
/* encoding26 */
/* A	B	C	D	E	F	G	H	I	J	K	L	M	N	O	P	Q	R	S	T	U	V	W	X	Y	Z  */
/* 1    2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26 */
/* 65   66  67  68  69  70  71  72  73  74  75  76  77  78  79  80  81  82  83  84  85  86  87  88  89  90 */

int encoding26(std::string column)
{
    size_t n = column.size();
    int r = 0;
    for (size_t i = 0; i < n; ++i) {
        char ch = column[n - 1 - i];
        r += std::pow(26, i) * (ch - 'A' + 1);
    }
    return r;
}

int main()
{
    std::cout << encoding26("ZZ") << std::endl;
    std::cout << encoding26("AA") << std::endl;
    std::cout << encoding26("D") << std::endl;
}
