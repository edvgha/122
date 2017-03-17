
int loop(int x, int n)
{
    int result = -1;
    int mask;
    for(mask = 1; mask != 0; mask = mask << n) {
        result ^= (x & mask);
    }
    return result;
}
