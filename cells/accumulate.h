#include "joiner.h"
#include <future>
#include <numeric>
#include <iterator>

template <typename Iterator, typename T>
struct accumulate_block
{
    public:
        T operator () (Iterator first, Iterator last)
        {
            return std::accumulate(first, last, T());
        }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);

    if (!length)
        return init;

    unsigned long const min_per_thead = 25;
    unsigned long const max_threads = (length + min_per_thead - 1) / min_per_thead;

    unsigned long const hardware_threads = std::thread::hardware_concurrency();

    unsigned long const num_threads = 
    std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    unsigned long const block_size = length / num_threads;

    std::vector<std::future<T>> futures(num_threads - 1);
    std::vector<std::thread> threads(num_threads - 1);
    join_threads jointer(threads);

    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        std::packaged_task<T(Iterator, Iterator)> task((accumulate_block<Iterator, T>()));
        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task), block_start, block_end);
        block_start = block_end;
    }
    T last_result = accumulate_block<Iterator, T>() (block_start, last);
    T result = init;
    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
        result += futures[i].get();
    }
    result += last_result;
    return result;
}
