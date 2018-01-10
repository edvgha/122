#pragma once 

#include <vector>
#include <thread>

class join_threads
{
    private:
        std::vector<std::thread>& threads;
    public:
        explicit join_threads(std::vector<std::thread>& t): threads(t) {}
        ~join_threads() 
        {
            for (unsigned long i = 0; i < threads.size(); ++i) {
                if (threads[i].joinable())
                    threads[i].join();
            }
        }
};
