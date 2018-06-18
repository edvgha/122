#include <iostream>
#include <stack>

class queue
{
public:
    void push(int d)
    {
        enqueue_.push(d);
    }

    int pop()
    {
        if (dequeue_.empty())
        {
            while (!enqueue_.empty())
            {
                dequeue_.push(enqueue_.top());
                enqueue_.pop();
            }
        }

        if (!dequeue_.empty())
        {
            int d = dequeue_.top();
            dequeue_.pop();
            return d;
        }
        return -1;
    }
private:
    std::stack<int> enqueue_;
    std::stack<int> dequeue_;
};

int main()
{
    queue qq;
    qq.push(1);
    qq.push(2);
    qq.push(3);
    qq.push(4);
    qq.push(5);
    std::cout << qq.pop() << std::endl;
    std::cout << qq.pop() << std::endl;
    std::cout << qq.pop() << std::endl;
    qq.push(6);
    qq.push(7);
    qq.push(8);
    qq.push(9);
    std::cout << qq.pop() << std::endl;
    std::cout << qq.pop() << std::endl;
    std::cout << qq.pop() << std::endl;
    qq.push(10);
    std::cout << qq.pop() << std::endl;
}
