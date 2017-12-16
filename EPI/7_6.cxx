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
std::shared_ptr<ListNode<int>> build()
{
    auto node = std::make_shared<ListNode<int>>();
    node -> data_ = 1;
    head = node;
    tail = node;

    auto r = head;
    for (size_t i = 1; i < n; ++i) {
        node = std::make_shared<ListNode<int>>();
        node -> data_ = i + 1;
        tail->next_ = node;
        tail = node;
        if (i == 5) {
            r = node;
        }
    }
    std::cout << "we should delete : " << r->data_ << std::endl;
    return r;
}

void print()
{
    auto node = head;
    while (node) {
        std::cout << node->data_ << std::endl;
        node = node -> next_;
    }
}

template <typename T>
void deleteNode(std::shared_ptr<ListNode<T>> node)
{
    node->data_ = node->next_->data_;
    node->next_ = node->next_->next_;
}

int main()
{
    auto n = build<13>();
    std::cout << "before" << std::endl;
    print();
    deleteNode(n);
    std::cout << "after" << std::endl;
    print();
}
