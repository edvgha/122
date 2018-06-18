#include <iostream>
#include <stack>

class stack
{
public:
    void push(int i)
    {
        if (stack_.empty())
        {
            stack_.push({i, i});
            return ;
        }

        auto [data, max] = stack_.top();
        if (i > max)
        {
            stack_.push({i, i});
            return;
        }

        stack_.push({i, max});
    }

    void pop()
    {
        stack_.pop();
    }

    bool empty()
    {
        return stack_.empty();
    }

    int top()
    {
        return stack_.top().first;
    }

    int max()
    {
        return stack_.top().second;
    }
private:
    std::stack<std::pair<int, int>> stack_;
};

int main()
{
    stack st;
    st.push(1);
    st.push(1);
    st.push(5);
    st.push(4);
    st.push(3);
    st.push(10);
    st.push(9);
    st.push(2);
    std::cout << st.top() << ' ' << st.max() << std::endl;
    st.pop();
    std::cout << st.top() << ' ' << st.max() << std::endl;
    st.pop();
    std::cout << st.top() << ' ' << st.max() << std::endl;
    st.pop();
    std::cout << st.top() << ' ' << st.max() << std::endl;
    st.pop();
    std::cout << st.top() << ' ' << st.max() << std::endl;
    st.pop();
    std::cout << st.top() << ' ' << st.max() << std::endl;
    st.pop();
    std::cout << st.top() << ' ' << st.max() << std::endl;
    st.pop();
    std::cout << st.top() << ' ' << st.max() << std::endl;
}
