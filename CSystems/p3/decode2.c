int decode2(int x, int y, int z);

int decode2(int x, int y, int z)
{
    int eax, edx;
    edx = (y - z);
    eax = edx;
    eax <<= 31;
    eax >>= 31;
    eax *= x;
    return edx ^ eax;
}
