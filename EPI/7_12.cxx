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

void pivot(int k)
{
    auto node = head;
    auto prevNode = head;
    prevNode = nullptr;
    auto pivot = prevNode;
    auto pEnd = pivot;

    while (node) {
        if (node->data_ < k) {
            prevNode = node;
            node = node->next_;
        } else if (node->data_ == k) {
            if (!pivot) {
                pivot = node;
                prevNode = node;
                node = node->next_;
            } else {
                prevNode->next_ = node->next_;
                node->next_ = nullptr;
                auto tmp = node;
                node = node->next_;
                tmp->next_ = pivot->next_
                pivot->next_ = tmp;
            }
        } else {
            assert(node->data_ > k);
            if (!pEnd) {
            } else {
            }
        }
    }
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
