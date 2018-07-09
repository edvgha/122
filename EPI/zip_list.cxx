#include <iostream>
#include <memory>

struct LNode
{
    int data;
    std::shared_ptr<LNode> next;

    LNode(int d): data(d), next(nullptr) {}
};

std::shared_ptr<LNode> list()
{
    std::shared_ptr<LNode> n1 = std::make_shared<LNode>(1);
    std::shared_ptr<LNode> n2 = std::make_shared<LNode>(2);
    std::shared_ptr<LNode> n3 = std::make_shared<LNode>(3);
    std::shared_ptr<LNode> n4 = std::make_shared<LNode>(4);
    std::shared_ptr<LNode> n5 = std::make_shared<LNode>(5);
    std::shared_ptr<LNode> n6 = std::make_shared<LNode>(6);
    n1 -> next = n2;
    n2 -> next = n3;
    n3 -> next = n4;
    n4 -> next = n5;
    n5 -> next = n6;
    return n1;
}

std::shared_ptr<LNode> middle_node(std::shared_ptr<LNode> head)
{
    auto p_slow = head;
    auto p_fast = head;
    while (true)
    {
        if (p_fast && p_fast -> next && p_fast -> next -> next)
        {
            p_slow = p_slow -> next;
            p_fast = p_fast -> next -> next;
        } 
        else 
        {
            return p_slow;
        }
    }
    return nullptr;
}

void show(std::shared_ptr<LNode> head)
{
    auto p = head;
    while (p)
    {
        std::cout << p -> data << std::endl;
        p = p -> next;
    }
}

void zip_list(std::shared_ptr<LNode> head)
{
    std::shared_ptr<LNode> mid = middle_node(head);
    std::shared_ptr<LNode> l2 = mid->next;
    mid->next = nullptr;
    while (l2)
    {
        auto tmp = l2->next;
        l2->next = head;
        head = l2;
        l2 = tmp;
    }

    auto l1 = head;
    mid = middle_node(head);
    l2 = mid->next;
    mid->next = nullptr;

    head = l2;
    while (l2)
    {
        auto tmp1 = l1 -> next;
        auto tmp2 = l2 -> next;
        l1 -> next = nullptr;
        l2 -> next = nullptr;
        l2 -> next = l1;
        l1 -> next = tmp2;
        l1 = tmp1;
        l2 = tmp2;
    }
    show(head);
}

int main()
{
    zip_list(list());
}
