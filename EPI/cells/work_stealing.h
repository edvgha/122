#include "work_stealing_queue.h"
#include "threadsafe_queue.h"
#include "joiner.h"
#include <vector>
#include <memory>
#include <future>
#include <atomic>

class thread_pool
{
    private:
        using task_type = function_wrapper;

    private:
        std::atomic_bool done;
        threadsafe_queue<task_type> pool_work_queue;
        std::vector<std::unique_ptr<work_stealing_queue>> queues;
        std::vector<std::thread> threads;
        join_threads joiner;

        static thread_local work_stealing_queue* local_work_queue;
        static thread_local unsigned my_index;

    private:
        void worker_thread(unsigned my_id)
        {
            my_index = my_id;
            local_work_queue = queues[my_index].get();
            while (! done)
                run_pending_task();
        }

        bool pop_task_from_local_queue(task_type& task)
        {
            printf("pop task from local queue\n");
            return local_work_queue && local_work_queue -> try_pop(task);
        }

        bool pop_task_from_pool_queue(task_type& task)
        {
            printf("pop task from work queue\n");
            return pool_work_queue . try_pop(task);
        }

        bool pop_task_from_other_thread_queue(task_type& task)
        {
            printf("pop task from other thread queue\n");
            for (unsigned i = 0; i < queues.size(); ++i) {
                unsigned const index = (my_index + i + 1) % queues.size();
                if (queues[index] -> try_steal(task))
                    return true;
            }
            return false;
        }
    public:
        thread_pool(): done(false), joiner(threads)
        {
            unsigned const thread_count = std::thread::hardware_concurrency();

            try {
                for (unsigned i = 0; i < thread_count; ++i) {
                    queues.push_back(std::unique_ptr<work_stealing_queue>(new work_stealing_queue));
                    threads.push_back(std::thread(&thread_pool::worker_thread, this, i));
                }
            } catch (...) {
                done = true;
                throw;
            }
        }

        ~thread_pool() 
        {
            done = true;
        }

        template <typename FunctionType>
        std::future<typename std::result_of<FunctionType()>::type> 
        submit(FunctionType f) 
        {
            using result_type = typename std::result_of<FunctionType()>::type;
            std::packaged_task<result_type()> task(f);
            std::future<result_type> res(task.get_future());
            if (local_work_queue)
                local_work_queue -> push(std::move(task));
            else 
                pool_work_queue.push(std::move(task));
            return res;
        }

        void run_pending_task()
        {
            task_type task;
            if (pop_task_from_local_queue(task) ||
                pop_task_from_pool_queue(task)  ||
                pop_task_from_other_thread_queue(task))
                task();
            else 
                std::this_thread::yield();
        }
};

thread_local work_stealing_queue* thread_pool::local_work_queue;
thread_local unsigned thread_pool::my_index;

//thread_pool pool;
