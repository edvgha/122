#include <iostream>
#include <vector>
#include <memory>
#include <queue>

template <typename T>
struct TreeNode 
{
	T data_;
	std::shared_ptr<TreeNode<T>> left_;
	std::shared_ptr<TreeNode<T>> right_;

	TreeNode(T t = 0) : data_(t) {}
};

std::shared_ptr<TreeNode<int>> root;

void build()
{
	root = std::make_shared<TreeNode<int>>(314);
	/*** level 1 ***/
	auto n1 = std::make_shared<TreeNode<int>>(6);
	auto n2 = std::make_shared<TreeNode<int>>(6);
	root -> left_ = n1;
	root -> right_ = n2;

	/*** level 2 ***/
	auto n3 = std::make_shared<TreeNode<int>>(271);
	auto n4 = std::make_shared<TreeNode<int>>(561);
	auto n5 = std::make_shared<TreeNode<int>>(2);
	auto n6 = std::make_shared<TreeNode<int>>(271);
	n1 -> left_ = n3;
	n1 -> right_ = n4;
	n2 -> left_ = n5;
	n2 -> right_ = n6;

	/*** level 3 ***/
	auto n7 = std::make_shared<TreeNode<int>>(28);
	auto n8 = std::make_shared<TreeNode<int>>(0);
	auto n9 = std::make_shared<TreeNode<int>>(3);
	auto n10 = std::make_shared<TreeNode<int>>(1);
	auto n11 = std::make_shared<TreeNode<int>>(28);
	n3 -> left_ = n7;
	n3 -> right_ = n8;
	n4 -> right_ = n9;
	n5 -> right_ = n10;
	n6 -> right_ = n11;

	/*** level 4 ***/
	auto n12 = std::make_shared<TreeNode<int>>(17);
	auto n13 = std::make_shared<TreeNode<int>>(401);
	auto n14 = std::make_shared<TreeNode<int>>(257);
	n9 -> left_ = n12;
	n10 -> left_ = n13;
	n10 -> right_ = n14;

	/*** level 5 ***/
	auto n15 = std::make_shared<TreeNode<int>>(641);
	n13 -> right_ = n15;
}

void print(std::shared_ptr<TreeNode<int>> n)
{
	if (!n) return ;
	std::cout << n -> data_ << std::endl;
	print(n -> left_);
	print(n -> right_);
}

std::vector<std::vector<int>> traverseIterBFS()
{
	std::queue<std::vector<std::shared_ptr<TreeNode<int>>>> queue;
	queue.push({root});
	std::vector<std::vector<int>> res;
	while (!queue.empty()) {
		auto vec = queue.front();
		queue.pop();
		std::vector<int> r;
		std::vector<std::shared_ptr<TreeNode<int>>> level;
		for (auto el : vec) {
			r.push_back(el -> data_);
			if (el -> left_)
				level.push_back(el -> left_);
			if (el -> right_) 
				level.push_back(el -> right_);
		}
		if (0 != level.size()) {
			queue.push(level);
		}
		res.push_back(r);
	}
	return res;
}

int main()
{
	build();
	//print(root);
	
	auto res = traverseIterBFS();
	for (auto e1 : res) {
		for (auto e2 : e1) 
			std::cout << e2 << ' ';
		std::cout << std::endl;
	}
	
}