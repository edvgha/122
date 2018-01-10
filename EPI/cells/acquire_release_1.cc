#include <iostream>
#include <atomic>
#include <future>
#include <cassert>

std::atomic_int sync(0);
std::atomic_int data[5];

void thread_1()
{
    std::cout << "start\n";
    data[0].store(42, std::memory_order_relaxed);
    data[1].store(97, std::memory_order_relaxed);
    data[2].store(17, std::memory_order_relaxed);
    data[3].store(-141, std::memory_order_relaxed);
    data[4].store(2003, std::memory_order_relaxed);
    sync.store(1, std::memory_order_release);
}

void thread_2()
{
    int expected = 1;
    while (! sync.compare_exchange_strong(expected, 2, std::memory_order_acq_rel))
        expected = 1;
}

void thread_3()
{
    while (sync.load(std::memory_order_acquire) < 2);
    std::cout << "done\n";
    assert(data[0].load(std::memory_order_relaxed) == 42);
    assert(data[1].load(std::memory_order_relaxed) == 97);
    assert(data[2].load(std::memory_order_relaxed) == 17);
    assert(data[3].load(std::memory_order_relaxed) == -141);
    assert(data[4].load(std::memory_order_relaxed) == 2003);
}

int main()
{
    std::future<void> f1 = std::async(thread_1);
    std::future<void> f2 = std::async(thread_2);
    std::future<void> f3 = std::async(thread_3);
    f1.wait();
    f2.wait();
    f3.wait();
}
