#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int data;
std::condition_variable cv;
std::mutex m;

void set()
{
    std::lock_guard<std::mutex> lg(m);
    data = 11;
    cv.notify_all();
}

void get(int i)
{
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, []{return data > 10;});
    std::cout << "data" << i << ": " << data << std::endl;
    //data = 9;
}

int main()
{
    std::thread t1(get, 1);
    std::thread t2(get, 2);
    std::thread t3(get, 3);
    std::thread t4(get, 4);
    std::thread t5(get, 5);
    std::thread t6(set);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
}
