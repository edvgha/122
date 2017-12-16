#include <iostream>
#include <memory>

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
    node -> data_ = 1;
    head = node;
    tail = node;

    for (size_t i = 1; i < n; ++i) {
        node = std::make_shared<ListNode<int>>();
        node -> data_ = i + 1;
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

void cyclicShift(size_t k)
{
    auto node = head;
    auto tail = head;
    size_t cnt = 0;
    while (node) {tail = node; node = node->next_; ++cnt;}
    k = k % cnt;
    node = head;
    for (size_t i = 0; i < (cnt - k - 1); ++i) {
        node = node->next_;
    }
    tail->next_ = head;
    head = node->next_;
    node->next_ = nullptr;
}

int main()
{
    build<13>();
    print();
    std::cout << "------" << std::endl;
    cyclicShift(25);
    std::cout << "------" << std::endl;
    print();
}
