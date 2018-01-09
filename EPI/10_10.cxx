#include <iostream>
#include <memory>

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

    for (size_t i = 1; i < n; ++i) {
        node -> next_ = std::make_shared<ListNode<int>>();
        node -> next_ -> data_ = n - i;
        node = node -> next_;
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

void ListSort()
{

}

int main()
{
	build();
	ListSort();
	print();
}