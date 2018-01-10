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

template <int n = 10>
void build()
{
    auto node = std::make_shared<ListNode<int>>();
    node -> data_ = n;
    head = node;

    auto r = head;
    for (size_t i = 1; i < n; ++i) {
        node -> next_ = std::make_shared<ListNode<int>>();
        node -> next_ -> data_ = n - i;
        node = node -> next_;
    }
    for (size_t i = 1; i < n; ++i) {
        node -> next_ = std::make_shared<ListNode<int>>();
        node -> next_ -> data_ = n - i;
        node = node -> next_;
    }
}

void print(std::shared_ptr<ListNode<int>> h)
{
    auto node = h;
    while (node) {
        std::cout << node->data_ << std::endl;
        node = node -> next_;
    }
}

std::shared_ptr<ListNode<int>> split_pos(std::shared_ptr<ListNode<int>> h)
{
    auto fast = h;
    auto slow = h;
    while (fast -> next_ && fast -> next_ -> next_) {
        slow = slow -> next_;
        fast = fast -> next_ -> next_;
    }
    return slow;
}

std::shared_ptr<ListNode<int>> merge(std::shared_ptr<ListNode<int>> a, std::shared_ptr<ListNode<int>> b)
{
    std::shared_ptr<ListNode<int>> h;
    if (a -> data_ <= b -> data_) {
        auto tmp = a -> next_;
        a -> next_ = nullptr;
        h = a;
        a = tmp;
    } else {
        auto tmp = b -> next_;
        b -> next_ = nullptr;
        h = b;
        b = tmp;
    }
    auto cur = h;

    while (a && b) {
        if (a -> data_ <= b -> data_) {
            auto tmp = a -> next_;
            a -> next_ = nullptr;
            cur -> next_ = a;
            cur = cur -> next_;
            a = tmp;
        } else {
            assert(a -> data_ > b -> data_);
            auto tmp = b -> next_;
            b -> next_ = nullptr;
            cur -> next_ = b;
            cur = cur -> next_;
            b = tmp;
        }
    }

    if (a) {
        cur -> next_ = a;
    } else {
        cur -> next_ = b;
    }
    return h;
}

std::shared_ptr<ListNode<int>> list_sort(std::shared_ptr<ListNode<int>> h)
{
    if (!h -> next_) 
        return h;
    auto pos = split_pos(h);
    auto n = pos -> next_;
    pos -> next_ = nullptr;
    auto l = list_sort(h);
    auto r = list_sort(n);
    return merge(l, r);
}

int main()
{
    build<12>();
    print(head);
    auto x = list_sort(head);
    std::cout << "----" << std::endl;
    print(x);
}
