#include "Tree.hpp"
#include <stack>

void preorder_i(std::unique_ptr<BinaryTreeNode<int>>& node)
{
	std::stack<BinaryTreeNode<int>*> stack;
	auto cur = node.get();
	stack.push(cur);
	while (!stack.empty()) {
		cur = stack.top();
		stack.pop();
		std::cout << cur -> c_ << ' ';
		auto cur1 = cur -> right_.get();
		if (cur1) 
			stack.push(cur1);
		auto cur2 = cur -> left_.get();
		if (cur2) 
			stack.push(cur2);
	}
}

void preorder_r(std::unique_ptr<BinaryTreeNode<int>>& node)
{
	if (! node) return ;
	std::cout << node -> c_ << ' ';
	preorder_r(node -> left_);
	preorder_r(node -> right_);
}

int main()
{
	build();
	preorder_r(root);
	std::cout << std::endl;
	preorder_i(root);
	std::cout << std::endl;
}