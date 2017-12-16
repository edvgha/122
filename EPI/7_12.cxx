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

void append(std::shared_ptr<ListNode<int>>& iter, std::shared_ptr<ListNode<int>>& node)
{
    iter->next_ = node;
    iter = iter->next_;

    auto tmp = node;
    node = node -> next_;
    tmp->next_ = nullptr;
}

void pivot(int k)
{
    auto node = head;
    auto less_head = std::make_shared<ListNode<int>>();
    auto less_iter = less_head;
    auto great_head = std::make_shared<ListNode<int>>();
    auto great_iter = great_head;
    auto equal_head = std::make_shared<ListNode<int>>();
    auto equal_iter = equal_head;

    while (node) {
        if (node -> data_ == k) {
            append(equal_iter, node);
        } else if (node -> data_ < k) {
            append(less_iter, node);
        } else {
            append(great_iter, node);
        }
    }

    head = less_head->next_;
    less_iter->next_ = equal_head->next_;
    equal_head->next_ = nullptr;
    equal_iter->next_ = great_head->next_;
    great_head->next_ = nullptr;
    great_iter->next_ = nullptr;
}

int main()
{
    build<13>();
    print();
    std::cout << "------" << std::endl;
    pivot(5);
    std::cout << "------" << std::endl;
    print();
}
