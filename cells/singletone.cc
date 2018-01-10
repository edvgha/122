#include <iostream>
#include <mutex>
#include <thread>
#include <functional>

class X
{
    private:
        int data_;
        mutable std::mutex m_;

    public:
        static X& instance() 
        {
            static X instance;
            return instance;
        }

        void print() const {
            std::lock_guard<std::mutex> lock(m_);
            std::cout << this << '\n';
        }

    private:
        X() = default;

    public:
        X(X&&) = delete;
        X(const X&) = delete;
        X& operator = (const X&) = delete;
        X& operator = (X&&) = delete;
        ~X() = default;
};

int main()
{
    std::thread t0(std::bind(&X::print, &X::instance()));
    std::thread t1(std::bind(&X::print, &X::instance()));
    std::thread t2(std::bind(&X::print, &X::instance()));
    std::thread t3(std::bind(&X::print, &X::instance()));
    std::thread t4(std::bind(&X::print, &X::instance()));
    std::thread t5(std::bind(&X::print, &X::instance()));
    std::thread t6(std::bind(&X::print, &X::instance()));
    std::thread t7(std::bind(&X::print, &X::instance()));
    std::thread t8(std::bind(&X::print, &X::instance()));
    std::thread t9(std::bind(&X::print, &X::instance()));
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
}
