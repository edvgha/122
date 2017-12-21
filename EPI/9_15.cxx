#include "Tree.hpp"

std::unique_ptr<BinaryTreeNode<int>>& find_left(std::unique_ptr<BinaryTreeNode<int>>& node)
{
    if (! node -> left_) 
        find_left(node -> right_);
    return node -> left_;
}

std::unique_ptr<BinaryTreeNode<int>>& find_right(std::unique_ptr<BinaryTreeNode<int>>& node)
{
    if (! node -> right_) 
        find_right(node -> left_);
    return node -> right_;
}

void exterior_left(std::unique_ptr<BinaryTreeNode<int>>& node)
{
    if (!node || !node -> left_) 
        return ;
    std::cout << node -> c_ << ' ';
    exterior_left(node -> left_);
}

void exterior_leaf(std::unique_ptr<BinaryTreeNode<int>>& node)
{
    if (!node)
        return ;

    if (!node -> right_ && !node -> left_) 
        std::cout << node -> c_ << ' ';

    exterior_leaf(node -> left_);
    exterior_leaf(node -> right_);
}

void exterior_right(std::unique_ptr<BinaryTreeNode<int>>& node)
{
    if (! node) 
        return ;
    if (node && !node -> right_) 
        return ;

    exterior_right(node -> right_);
    std::cout << node -> c_ << ' ';
}

void exterior(std::unique_ptr<BinaryTreeNode<int>>& node)
{
    std::cout << node -> c_ << ' ';
    exterior_left(find_left(node));
    exterior_leaf(node);
    exterior_right(find_right(node));
}

int main()
{
    build();
    exterior(root);
    std::cout << std::endl;
}
