#include <iostream>
#include <memory>
#include <queue>

template <typename T>
struct TreeNode
{
    T data_;
    std::unique_ptr<TreeNode<T>> left_;
    std::unique_ptr<TreeNode<T>> right_;
    TreeNode<T>* next_;

    TreeNode(T t) : data_(t)
                  , left_(nullptr)
                  , right_(nullptr)
                  , next_(nullptr)
    {}
};

struct Tree
{
using node = TreeNode<char>;
std::unique_ptr<node> root_;

void build_horizontal_next()
{
    build_horizontal_next_internal(root_);
}

void build_horizontal_next_internal(std::unique_ptr<node>& n)
{
    if (! n) 
        return ;
    build_horizontal_next_internal(n -> right_);
    build_horizontal_next_internal(n -> left_);

    if (! n -> right_ || ! n -> left_)
        return ;

    node* left = n -> left_ . get();
    node* right = n -> right_ . get();
    while (left)
    {
        left -> next_ = right;
        left = left -> right_.get();
        right = right -> left_.get();
    }
}

void print_inorder()
{
    print_inorder_internal(root_);
}

void print_inorder_internal(std::unique_ptr<node>& node)
{
    if (! node ) return ;

    print_inorder_internal(node -> left_);
    std::cout << node -> data_ << " --> ";
    if (node -> next_)
        std::cout << node -> next_ -> data_ << std::endl;
    else 
        std::cout << "no_next_node" << std::endl;
    print_inorder_internal(node -> right_);
}

void build9_6()
{
    //--------------------------------------------------//
    std::unique_ptr<node> d = std::make_unique<node>('D');
    std::unique_ptr<node> e = std::make_unique<node>('E');
    std::unique_ptr<node> g = std::make_unique<node>('G');
    std::unique_ptr<node> h = std::make_unique<node>('H');
    std::unique_ptr<node> k = std::make_unique<node>('K');
    std::unique_ptr<node> l = std::make_unique<node>('L');
    std::unique_ptr<node> n = std::make_unique<node>('N');
    std::unique_ptr<node> o = std::make_unique<node>('O');
    //--------------------------------------------------//
    std::unique_ptr<node> c = std::make_unique<node>('C');
    std::unique_ptr<node> f = std::make_unique<node>('F');
    std::unique_ptr<node> j = std::make_unique<node>('J');
    std::unique_ptr<node> m = std::make_unique<node>('M');
    //--------------------------------------------------//
    std::unique_ptr<node> b = std::make_unique<node>('B');
    std::unique_ptr<node> i = std::make_unique<node>('I');
    //--------------------------------------------------//
    root_ = std::make_unique<node>('A');
    //--------------------------------------------------//
    c -> left_ = std::move(d);
    c -> right_ = std::move(e);
    f -> left_ = std::move(g);
    f -> right_ = std::move(h);
    j -> left_ = std::move(k);
    j -> right_ = std::move(l);
    m -> left_ = std::move(n);
    m -> right_ = std::move(o);
    //-----------------------//
    b -> left_ = std::move(c);
    b -> right_ = std::move(f);
    i -> left_ = std::move(j);
    i -> right_ = std::move(m);
    //-----------------------//
    root_ -> left_ = std::move(b);
    root_ -> right_ = std::move(i);
}

};

int main()
{
    Tree tree1;
    tree1.build9_6();
    tree1.build_horizontal_next();
    tree1.print_inorder();
}
