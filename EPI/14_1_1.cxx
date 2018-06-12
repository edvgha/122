#include <iostream>
#include <memory>
#include <queue>

template <typename T, typename M>
struct TreeNode
{
    T data1_;
    M data2_;
    std::unique_ptr<TreeNode<T, M>> left_;
    std::unique_ptr<TreeNode<T, M>> right_;

    TreeNode(T t, M m) : data1_(t)
                       , data2_(m)
                       , left_(nullptr)
                       , right_(nullptr)
    {}
};

struct Tree
{
using node = TreeNode<int, char>;
std::unique_ptr<node> root_;

bool isBst_iter()
{
    struct Item 
    {
        int lhs_;
        int rhs_;
        node* ptr_;
    };

    std::queue<Item> queue;

    Item item = {-1000, +1000, root_.get() };
    queue.push(item);
    while (! queue.empty()) 
    {
        Item item = queue.front();
        queue.pop();
        //std::cout << "node: " << item.ptr_ -> data1_ << " [" << item.lhs_ << ", " << item.rhs_ << "]" << std::endl;
        if (item.ptr_ -> data1_ > item.rhs_ || 
            item.ptr_ -> data1_ < item.lhs_) 
            return false;

        if (item.ptr_ -> left_)
            queue.push({item.lhs_, item.ptr_ -> data1_, item.ptr_ -> left_.get()});

        if (item.ptr_ -> right_)
            queue.push({item.ptr_ -> data1_, item.rhs_, item.ptr_ -> right_.get()});
    }
    return true;
}

bool isBST() const 
{
    isBST_internalt(root_, -1000, +1000);
}

bool isBST_internalt(const std::unique_ptr<node>& node, int lhs, int rhs) const
{
    if (! node ) 
        return true;

    if (node -> data1_ < lhs || node -> data1_ > rhs)
        return false;

    return isBST_internalt(node -> right_, node -> data1_, rhs) && isBST_internalt(node -> left_, lhs, node -> data1_);
}

void print_inorder()
{
    print_inorder_internal(root_);
}

void print_inorder_internal(std::unique_ptr<node>& node)
{
    if (! node ) return ;

    print_inorder_internal(node -> left_);
    std::cout << node -> data1_ << std::endl;
    print_inorder_internal(node -> right_);
}

void build14_1()
{
    std::unique_ptr<node> n13 = std::make_unique<node>(13, 'H');
    std::unique_ptr<node> n17 = std::make_unique<node>(17, 'G');
    std::unique_ptr<node> n11 = std::make_unique<node>(11, 'F');
    std::unique_ptr<node> n7 = std::make_unique<node>(7, 'B');
    std::unique_ptr<node> n5 = std::make_unique<node>(5, 'E');
    std::unique_ptr<node> n2 = std::make_unique<node>(2, 'D');
    std::unique_ptr<node> n3 = std::make_unique<node>(3, 'C');
    std::unique_ptr<node> n31 = std::make_unique<node>(31, 'M');
    std::unique_ptr<node> n29 = std::make_unique<node>(29, 'L');
    std::unique_ptr<node> n37 = std::make_unique<node>(37, 'K');
    std::unique_ptr<node> n41 = std::make_unique<node>(41, 'N');
    std::unique_ptr<node> n23 = std::make_unique<node>(23, 'J');
    std::unique_ptr<node> n53 = std::make_unique<node>(53, 'P');
    std::unique_ptr<node> n47 = std::make_unique<node>(47, 'O');
    std::unique_ptr<node> n43 = std::make_unique<node>(43, 'I');
    root_ = std::make_unique<node>(19, 'A');

    n17 -> left_ = std::move(n13);
    n11 -> right_ = std::move(n17);
    n7 -> right_ = std::move(n11);
    n3 -> left_ = std::move(n2);
    n3 -> right_ = std::move(n5);
    n7 -> left_ = std::move(n3);
    root_ -> left_ = std::move(n7);

    n29 -> right_ = std::move(n31);
    n37 -> left_ = std::move(n29);
    n37 -> right_ = std::move(n41);
    n23 -> right_ = std::move(n37);
    n47 -> right_ = std::move(n53);
    n43 -> right_ = std::move(n47);
    n43 -> left_ = std::move(n23);
    root_ -> right_ = std::move(n43);
}

void build9_1()
{
    root_ = std::make_unique<node>(314, 'A');
    std::unique_ptr<node> n6_1 = std::make_unique<node>(6, 'B');
    std::unique_ptr<node> n6_2 = std::make_unique<node>(6, 'I');
    std::unique_ptr<node> n271_1 = std::make_unique<node>(271, 'C');
    std::unique_ptr<node> n561 = std::make_unique<node>(561, 'F');
    std::unique_ptr<node> n2 = std::make_unique<node>(2, 'J');
    std::unique_ptr<node> n271_2 = std::make_unique<node>(271, 'O');
    std::unique_ptr<node> n28_1 = std::make_unique<node>(28, 'D');
    std::unique_ptr<node> n0 = std::make_unique<node>(0, 'E');
    std::unique_ptr<node> n3 = std::make_unique<node>(3, 'G');
    std::unique_ptr<node> n1 = std::make_unique<node>(1, 'K');
    std::unique_ptr<node> n28_2 = std::make_unique<node>(28, 'P');
    std::unique_ptr<node> n17 = std::make_unique<node>(17, 'H');
    std::unique_ptr<node> n401 = std::make_unique<node>(401, 'L');
    std::unique_ptr<node> n257 = std::make_unique<node>(257, 'N');
    std::unique_ptr<node> n641 = std::make_unique<node>(641, 'M');

    n401 -> right_ = std::move(n641);
    n1 -> left_ = std::move(n401);
    n1 -> right_ = std::move(n257);
    n2 -> right_ = std::move(n1);
    n271_2 -> right_ = std::move(n28_2);
    n6_2 -> left_ = std::move(n2);
    n6_2 -> right_ = std::move(n271_2);
    n3 -> left_ = std::move(n17);
    n561 -> right_ = std::move(n3);
    n271_1 -> left_ = std::move(n28_1);
    n271_1 -> right_ = std::move(n0);
    n6_1 -> left_ = std::move(n271_1);
    n6_1 -> right_ = std::move(n561);
    root_ -> left_ = std::move(n6_1);
    root_ -> right_ = std::move(n6_2);
}

};

int main()
{
    Tree tree1;
    tree1.build14_1();
    Tree tree2;
    tree2.build9_1();
    printf("------------\n");
    //std::cout << std::boolalpha << tree1.isBST() << std::endl;
    //std::cout << std::boolalpha << tree2.isBST() << std::endl;
    std::cout << std::boolalpha << tree1.isBst_iter() << std::endl;
    std::cout << std::boolalpha << tree2.isBst_iter() << std::endl;
}
