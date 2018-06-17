#include <iostream>
#include <queue>
#include <algorithm>

void almost_sorted(std::vector<int>& arr, int k)
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> pqueue;
    for (size_t i = 0; i < k; ++i) 
        pqueue.push(arr[i]);
    size_t i = 0;
    for (size_t j = k; j < arr.size(); ++j)
    {
        arr[i++] = pqueue.top();
        pqueue.pop();
        pqueue.push(arr[j]);
    }
    while (!pqueue.empty())
    {
        arr[i++] = pqueue.top();
        pqueue.pop();
    }
}

int main()
{
    std::vector<int> arr = {3, -1, 2, 6, 4, 5, 8};
    almost_sorted(arr, 2);
    //{-1, 2, 3, 4, 5, 6, 8}
    for (auto el : arr)
        std::cout << el << ' ';
    std::cout << std::endl;
}
