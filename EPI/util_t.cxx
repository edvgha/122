template <typename T>
void printBinary(T d)
{
    uint8_t n = 8 * sizeof(d);
	std::string s(n, 'x');
	for (uint8_t i = 0; i < n; ++i) {
		s[n - 1 - i] = static_cast<char>('0' + ((d >> i) & 0x1));
	}
	std::cout << s << std::endl;
}
