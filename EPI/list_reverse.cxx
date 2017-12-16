#include <iostream>
#include <memory>
#include <cassert>

template <typename T>
struct ListNode
{
    T data_;
    std::shared_ptr<ListNode<T>> next_;
};

std::shared_ptr<ListNode<int>> head;
std::shared_ptr<ListNode<int>> tail;

template <int n = 10>
void build()
{
    auto node = std::make_shared<ListNode<int>>();
    node -> data_ = n;
    head = node;
    tail = node;

    for (size_t i = 1; i < n; ++i) {
        node = std::make_shared<ListNode<int>>();
        node -> data_ = n - i;
        tail->next_ = node;
        tail = node;
    }
}

void print()
{
    auto node = head;
    while (node) {
        std::cout << node->data_ << std::endl;
        node = node -> next_;
    }
}

void reverse(std::shared_ptr<ListNode<int>>& node)
{
    if (!node->next_) {
        return;
    }
    reverse(node->next_);
    auto tmp = node->next_;
    tmp->next_ = node;
    node->next_ = nullptr;
}

void reverse()
{
    reverse(head);

    while (tail) {
        std::cout << tail->data_ << std::endl;
        tail = tail -> next_;
    }
}

int main()
{
    build<13>();
    print();

    std::cout << "-----" << std::endl;

    reverse();
}