#pragma once

#include "function_wrapper.h"
#include "threadsafe_queue.h"
#include "joiner.h"
#include <queue>
#include <future>
#include <mutex>
#include <thread>

class thread_pool {
    private:
        using local_queue_type = std::queue<function_wrapper>;

    private:
        std::atomic_bool done;
        threadsafe_queue<function_wrapper> pool_work_queue;
        static thread_local std::unique_ptr<local_queue_type> local_work_queue;
        std::vector<std::thread> threads;
        join_threads joiner;

    private:
        void worker_thread()
        {
            local_work_queue.reset(new local_queue_type);

            while (!done) {
                run_pending_task();
            }
        }

    public:
        thread_pool(): done(false), joiner(threads)
        {
            unsigned const thread_count = std::thread::hardware_concurrency();
            try {
                for (unsigned i = 0; i < thread_count; ++i) {
                    threads.push_back(std::thread(&thread_pool::worker_thread, this));
                }
            } catch( ... ) {
                done = true;
                throw;
            }
        }
        ~thread_pool()
        {
            done = true;
        }
    public:
        template<typename FunctionType>
        std::future<typename std::result_of<FunctionType()>::type>
        submit(FunctionType f)
        {
            using result_type = typename std::result_of<FunctionType()>::type;
            std::packaged_task<result_type()> task(f);
            std::future<result_type> res(task.get_future());
            if (local_work_queue) {
                printf("submit to local queue\n");
                local_work_queue -> push(std::move(task));
            } else {
                printf("submit to global queue\n");
                pool_work_queue.push(std::move(task));
            }
            return res;
        }

        void run_pending_task()
        {
            function_wrapper task;
            if (local_work_queue && !local_work_queue -> empty()) {
                printf("run local task\n");
                task = std::move(local_work_queue -> front());
                local_work_queue -> pop();
                task();
            } else if (pool_work_queue.try_pop(task)) {
                printf("run global task\n");
                task();
            } else {
                std::this_thread::yield();
            }
        }
};

thread_local std::unique_ptr<thread_pool::local_queue_type> thread_pool::local_work_queue;

//thread_pool pool;
