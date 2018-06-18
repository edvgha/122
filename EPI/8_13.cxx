#include <iostream>
#include <memory>

template <typename T>
struct LNode
{
    T data_;
    std::shared_ptr<LNode<T>> next_;

    LNode(T t) : data_(t), next_(nullptr) {}
};


struct List
{
using node = LNode<int>;
std::shared_ptr<node> head_;

void buildl1()
{
    head_ = std::make_shared<node>(3);
    std::shared_ptr<node> n2 = std::make_shared<node>(1);
    std::shared_ptr<node> n3 = std::make_shared<node>(4);
    head_ -> next_ = n2;
    n2 -> next_ = n3;
}

void buildl2()
{
    head_ = std::make_shared<node>(7);
    std::shared_ptr<node> n2 = std::make_shared<node>(0);
    std::shared_ptr<node> n3 = std::make_shared<node>(9);
    head_ -> next_ = n2;
    n2 -> next_ = n3;
}

void buildl3()
{
    head_ = std::make_shared<node>(0);
    std::shared_ptr<node> n2 = std::make_shared<node>(0);
    std::shared_ptr<node> n3 = std::make_shared<node>(5);
    head_ -> next_ = n2;
    n2 -> next_ = n3;
}

void add(std::shared_ptr<node> l1, std::shared_ptr<node> l2)
{
    int carry = 0;

    std::shared_ptr<node> cur = std::make_shared<node>(0);
    head_ = cur;
    while (l1 && l2)
    {
        int d = l1 -> data_ + l2 -> data_ + carry;
        if (d >= 10)
        {
            carry = 1;
            d -= 10;
        }
        else 
        {
            carry = 0;
        }
        
        std::shared_ptr<node> n = std::make_shared<node>(d);
        cur -> next_ = n;
        cur = n;
        l1 = l1 -> next_;
        l2 = l2 -> next_;
    }

    if (l1)
    {
        cur -> next_ = l1;
    }
    else
    {
        cur -> next_ = l2;
    }
    auto prev = cur;
    cur = cur -> next_;
    while (cur)
    {
        if (carry == 1)
        {
            cur -> data_ += 1;
            if (cur -> data_ == 10)
            {
                cur -> data_ == 0;
                carry = 1;
            }
            else 
            {
                carry = 0;
            }
        }
        prev = cur;
        cur = cur -> next_;
    }
    if (carry == 1)
    {
        prev -> next_ = std::make_shared<node>(1);
    }
    auto tmp = head_;
    head_ = head_ -> next_;
    tmp -> next_ = nullptr;
}

void print() const
{
    auto node = head_;
    while (node)
    {
        std::cout << node -> data_ << std::endl;
        node = node -> next_;
    }
}

};

int main()
{
    List l1;
    l1.buildl3();
    List l2;
    l2.buildl3();
    List l3;
    l3.add(l1 . head_, l2 . head_);
    l3.print();
}
