#include <vector>
#include "Tree.hpp"

std::vector<char> path_to(const std::unique_ptr<BinaryTreeNode<int>>& n, char c)
{
	if (c == n -> c_) {
		return {c};
	}
	std::vector<char> r = { n -> c_ };

	if (n -> left_) {
		auto v = path_to(n -> left_, c);
		if (*v.rbegin() == c) {
			r.insert(r.end(), v.begin(), v.end());
			return r;
		}
	}
	if (n -> right_) {
		auto v = path_to(n -> right_, c);
		if (*v.rbegin() == c) {
			r.insert(r.end(), v.begin(), v.end());
			return r;
		}
	}
	return r;
}

char LCA(const std::unique_ptr<BinaryTreeNode<int>>& n1, const std::unique_ptr<BinaryTreeNode<int>>& n2)
{
	auto n1Path = path_to(root, n1 -> c_);
	auto n2Path = path_to(root, n2 -> c_);
	if (n1Path.size() > n2Path.size() && n2Path[n2Path.size() - 1] == n1Path[n2Path.size() - 1])
		return n2Path[n2Path.size() - 1];

	if (n2Path.size() > n1Path.size() && n1Path[n1Path.size() - 1] == n2Path[n1Path.size() - 1])
		return n1Path[n1Path.size() - 1];
	size_t min = std::min(n1Path.size(), n2Path.size());
	for (int i = min - 1; i >= 0; --i) {
		if (n2Path[i] == n1Path[i])
			return n2Path[i];
	}
	return '?';
}

int main()
{
	build();
	//char c = LCA(root->right_->left_->right_->left_->right_, root->right_->left_->right_->right_);
	//char c = LCA(root->right_->left_->right_->left_->right_, root->left_->right_->right_->left_);
	char c = LCA(root->left_, root->left_->left_);
	std::cout << c << std::endl;
	//display(root);
}