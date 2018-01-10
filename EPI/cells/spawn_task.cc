#include <iostream>
#include <future>
#include <thread>
#include <type_traits>

template<typename F, typename A>
std::future<typename std::result_of<F(A&&)>::type>  spawn_task(F&& f, A&& a)
{
    using result_type = typename std::result_of<F(A&&)>::type;
    std::packaged_task<result_type(A&&)> task(std::move(f));
    std::future<result_type> res(task.get_future());
    std::thread t(std::move(task), std::move(a));
    t.detach();
    return res;
}

int task(int a)
{
    return a * 2;
}

int main()
{
    std::future<int> r = spawn_task(task, 5);
    std::cout << r.get() << std::endl;
}
