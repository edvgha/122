#include "Tree.hpp"
#include <stack>
#include <cassert>

/*
	Traverse the left subtree, visit the root, then traverse the right subtree
*/
void inorder_traversal_i(const std::unique_ptr<BinaryTreeNode<int>>& node)
{
	if ( ! node) 
		return ;

	std::stack<BinaryTreeNode<int>*> stack;
	auto cur = node.get();
	while (!stack.empty() || cur) {
		if (cur) {
			stack.push(cur);
			cur = cur -> left_.get();
		} else {
			cur = stack.top();
			std::cout << cur -> c_ << ' ';
			stack.pop();
			cur = cur -> right_.get();
		}
	}
}

void inorder_traversal_r(const std::unique_ptr<BinaryTreeNode<int>>& node)
{
	if (! node) 
		return ;
	inorder_traversal_r(node -> left_);
	std::cout << node -> c_ << ' ';
	inorder_traversal_r(node -> right_);
}

int main(int argc, char const *argv[])
{
	build();
	inorder_traversal_r(root);
	std::cout << std::endl;
	inorder_traversal_i(root);
	return 0;
}