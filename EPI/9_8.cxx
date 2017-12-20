#include "Tree.hpp"
#include <stack>

void preorder_i1(std::unique_ptr<BinaryTreeNode<int>>& node)
{
	std::stack<BinaryTreeNode<int>*> left;
	std::stack<BinaryTreeNode<int>*> right;
	std::cout << node -> c_ << ' ';
	if (node -> left_)
		left.push(node -> left_.get());
	if (node -> right_)
		right.push(node -> right_.get());
	while (!left.empty() && !right.empty()) {
		if (!left.empty()) {
			std::cout << "DDDD" << std::endl;
			std::unique_ptr<BinaryTreeNode<int>> n(left.top());
			std::cout << "XXXXX" << std::endl;
			std::cout << n -> c_ << ' ';
			left.pop();
			if (n -> left_) 
				left.push(n -> left_.get());
			if (n -> right_)
				right.push(n -> right_.get());
			std::cout << "YYYYY" << std::endl;
		} else if (! right.empty()) {
			std::cout << "zzzzzz" << std::endl;
			std::unique_ptr<BinaryTreeNode<int>> n(right.top());
			std::cout << n -> c_ << ' ';
			right.pop();
			if (n -> left_) 
				left.push(n -> left_.get());
			if (n -> right_)
				right.push(n -> right_.get());
		}
	}
}

void preorder_i2(std::unique_ptr<BinaryTreeNode<int>>& node)
{
	std::stack<BinaryTreeNode<int>*> stack;
	std::cout << node -> c_ << ' ';
	
	if (node -> right_) 
		stack.push(node -> right_.get());
	if (node -> left_)
		stack.push(node -> left_.get());
	while (!stack.empty()) {
		std::unique_ptr<BinaryTreeNode<int>> n(stack.top());
		std::cout << n -> c_ << ' ';
		
		if (node -> right_) 
			stack.push(n -> right_.get());
		if (n -> left_)
			stack.push(n -> left_.get());
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
	std::cout << "-----" << std::endl;
	preorder_i1(root);
	std::cout << std::endl;
}