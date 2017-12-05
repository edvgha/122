#define R 5
#define S 9
#define T 11

int A[R][S][T];

int store_ele (int i, int j, int k, int* dest)
{
    *dest = A[i][j][k];
    return sizeof(A);
}
