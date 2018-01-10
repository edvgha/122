#include <iostream>
#include <future>

void task_lambda(int a, int b)
{
    std::packaged_task<int(int, int)> task([](int a, int b) { return a + b; });
    std::future<int> r = task.get_future();
    task(a, b);
    std::cout << r.get() << std::endl;
}

double task_lambda1(double a, double b)
{
    std::packaged_task<double(double, double)> task([](double a, double b) { return a / b; });
    std::future<double> f = task.get_future();
    std::thread t(std::move(task), a, b);
    t.join();
    return f.get();
}

double task_lambda2(double a, double b)
{
    std::packaged_task<double(double, double)> task([](double a, double b) { return a * b; });
    std::future<double> f = task.get_future();
    std::future<void> fu = std::async(std::move(task), a, b);
    fu.wait();
    return f.get();
}

int main()
{
    task_lambda(4, 5);
    std::cout << task_lambda1(4.34352, 1.343565) << std::endl;
    std::cout << task_lambda2(4.34352, 1.343565) << std::endl;
}
