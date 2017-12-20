#include <iostream>
#include "Tree.hpp"

bool RootToLeaf(std::unique_ptr<BinaryTreeNode<int>>& node, int weight)
{
	if (!node)
		return false;

	if (! node -> left_ && ! node -> right_ && node -> data_ == weight) 
		return true;

	return RootToLeaf(node -> left_, weight - node -> data_) || RootToLeaf(node -> right_, weight - node -> data_);
}

int main()
{
	build();
	std::cout << std::boolalpha << RootToLeaf(root, 619) << std::endl;
}