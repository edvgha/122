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
    tail->next_ = head;
}

void print()
{
    auto node = head;
    while (node) {
        std::cout << node->data_ << std::endl;
        node = node -> next_;
    }
}

bool hasCycle()
{
    auto itSlow = head;
    auto itFast = head;
    while (itSlow && itFast) {
        std::cout << "iter" << std::endl;
        itSlow = itSlow->next_;
        itFast = itFast->next_ ? itFast->next_->next_ : nullptr;
        if ((itFast == itSlow) && itSlow && itFast) {
            std::cout << itFast->data_ << ' ' << itSlow->data_ << std::endl;
            return true;
        }
    }
    return false;
}

int main()
{
    build<13>();
    std::cout << std::boolalpha << hasCycle() << std::endl;
    //print();
}
