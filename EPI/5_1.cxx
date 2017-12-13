#include <iostream>
#include <array>
#include <cassert>

void swap(int a, int b)
{
    int t = a;
    a = b;
    b = t;
}

template<uint32_t n>
void D_Flag(std::array<int, n>& arr, uint32_t pivotIndex)
{
    assert(0 <= pivotIndex && pivotIndex < n);
    int pivot = arr[pivotIndex];
    std::cout << "pivot = " << pivot << std::endl;
    uint32_t lIndex = 0;
    uint32_t pIndex = pivotIndex;
    uint32_t pIndex2 = pivotIndex;
    uint32_t gIndex = n - 1;
    while (lIndex < pIndex || gIndex > pIndex2) {
        for (auto el : arr) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
        std::cout << "lIndex: " << lIndex << " pIndex: " << pIndex << " pIndex2: " << pIndex2 << " gIndex: " << gIndex << std::endl;
        if (lIndex < pIndex) {
            if (arr[lIndex] < pivot) {
                ++lIndex;
            } else if (arr[lIndex] == pivot) {
                if (lIndex + 1 == pIndex) {
                    --pIndex;
                } else {
                    int t = arr[pIndex - 1];
                    arr[pIndex - 1] = pivot;
                    arr[lIndex] = t;
                    --pIndex;
                }
            } else {
                assert(arr[lIndex] > pivot);
                if (lIndex + 1 == pIndex) {
                    int t = arr[lIndex];
                    arr[lIndex] = pivot;
                    arr[pIndex2] = t;
                    --pIndex2;
                    --pIndex;
                } else {
                    int t = arr[lIndex];
                    arr[lIndex] = arr[pIndex - 1];
                    arr[pIndex - 1] = pivot;
                    arr[pIndex2] = t;
                    --pIndex2;
                    --pIndex;
                }
            }
        } else {
            assert(gIndex > pIndex2);
            if (arr[gIndex] > pivot) {
                --gIndex;
            } else if (arr[gIndex] == pivot) {
                if (gIndex - 1 == pIndex2) {
                    ++pIndex2;
                } else {
                    int t = arr[pIndex2 + 1];
                    arr[pIndex2 + 1] = pivot;
                    arr[gIndex] = t;
                    ++pIndex2;
                }
            } else {
                assert(arr[gIndex] < pivot);
                if (gIndex - 1 == pIndex2) {
                    int t = arr[gIndex];
                    arr[gIndex] = pivot;
                    arr[pIndex] = t;
                    ++pIndex;
                    ++pIndex2;
                } else {
                    int t = arr[gIndex];
                    arr[gIndex] = arr[pIndex2 + 1];
                    arr[pIndex2 + 1] = pivot;
                    arr[pIndex] = t;
                    ++pIndex;
                    ++pIndex2;
                }
            }
        }
    }
}

int main()
{
    const uint32_t n = 7;
    std::array<int, n> arr = {0, 1, 2, 0, 2, 1, 1};
    D_Flag<n>(arr, 3);
    std::cout << std::endl;
    for (auto el : arr) {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
}
