#pragma once 

#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>

template <typename T>
class threadsafe_queue
{
    private:
        struct node {
            std::shared_ptr<T> data_;
            std::unique_ptr<node> next_;
        };

    private:
        std::mutex head_mutex_;
        std::unique_ptr<node> head_;
        std::mutex tail_mutex_;
        node* tail_;
        std::condition_variable data_cond_;

    public:
        threadsafe_queue(): head_(new node), tail_(head_.get()) {}
        threadsafe_queue(const threadsafe_queue& other) = delete;
        threadsafe_queue& operator =(const threadsafe_queue& other) = delete;
        
    private:
        node* get_tail()
        {
            std::lock_guard<std::mutex> tail_lock(tail_mutex_);
            return tail_;
        }

        std::unique_ptr<node> pop_head()
        {
            std::unique_ptr<node> old_head = std::move(head_);
            head_ = std::move(old_head -> next_);
            return old_head;
        }

        std::unique_lock<std::mutex> wait_for_data()
        {
            std::unique_lock<std::mutex> head_lock(head_mutex_);
            data_cond_.wait(head_lock, [&] { return head_.get() != get_tail(); });
            return std::move(head_lock);
        }

        std::unique_ptr<node> wait_pop_head()
        {
            std::unique_lock<std::mutex> head_lock(wait_for_data());
            return pop_head();
        }

        std::unique_ptr<node> try_pop_head()
        {
            std::lock_guard<std::mutex> head_lock(head_mutex_);
            if (head_.get() == get_tail())
                return std::unique_ptr<node>();
            return pop_head();
        }

        std::unique_ptr<node> try_pop_head(T& value)
        {
            std::lock_guard<std::mutex> head_lock(head_mutex_);
            if (head_.get() == get_tail()) 
                return std::unique_ptr<node>();
            value = std::move(*head_ -> data_);
            return pop_head();
        }

    public:
        std::shared_ptr<T> try_pop()
        {
            std::unique_ptr<node> old_head = try_pop_head();
            return old_head ? old_head->data_ : std::shared_ptr<T>();
        }

        bool try_pop(T& value)
        {
            std::unique_ptr<node> const old_head = try_pop_head(value);
            return (old_head != nullptr);
        }

        std::shared_ptr<T> wait_and_pop()
        {
            std::unique_ptr<node> const old_head = wait_pop_head();
            return old_head -> data_;
        }

        void wait_and_pop(T& value)
        {
            std::unique_ptr<node> const old_head = wait_pop_head(value);
        }

        void push(T new_value)
        {
            std::shared_ptr<T> new_data(
                std::make_shared<T>(std::move(new_value)));
            std::unique_ptr<node> p(new node);
            {
                std::lock_guard<std::mutex> tail_lock(tail_mutex_);
                tail_->data_ = new_data;
                node* const new_tail = p.get();
                tail_->next_ = std::move(p);
                tail_ = new_tail;
            }
            data_cond_.notify_one();
        }

        bool empty()
        {
            std::lock_guard<std::mutex> head_lock(head_mutex_);
            return (head_.get() == get_tail());
        }
};
