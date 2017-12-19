#include <iostream>
#include <stack>

template <typename T>
class Queue
{
    public:
        void enqueue(T t)
        {
            enqueue_.push(t);
        }
        T dequeue() noexcept(false)
        {
            if (dequeue_.empty()) {
                if (enqueue_.empty()) {
                    throw std::logic_error("tried to dequeue from empty queue");
                } else {
                    while (!enqueue_.empty()) {
                        dequeue_.push(enqueue_.top());
                        enqueue_.pop();
                    }
                }
            }
            T t = dequeue_.top();
            dequeue_.pop();
            return t;
        }
    private:
        std::stack<T> enqueue_;
        std::stack<T> dequeue_;
};

int main()
{
    try {
        Queue<int> queue;
        queue.enqueue(1);
        std::cout << queue.dequeue() << std::endl;
        queue.enqueue(2);
        std::cout << queue.dequeue() << std::endl;
        queue.enqueue(3);
        std::cout << queue.dequeue() << std::endl;
        queue.enqueue(4);
        queue.enqueue(5);
        std::cout << queue.dequeue() << std::endl;
        std::cout << queue.dequeue() << std::endl;
        queue.enqueue(6);
        std::cout << queue.dequeue() << std::endl;
        queue.enqueue(7);
        queue.enqueue(8);
        queue.enqueue(9);
        std::cout << queue.dequeue() << std::endl;
        std::cout << queue.dequeue() << std::endl;
        std::cout << queue.dequeue() << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
