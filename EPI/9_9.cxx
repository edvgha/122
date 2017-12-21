#include <cassert>
#include "Tree.hpp"

char kth_inorder(const std::unique_ptr<BinaryTreeNode<int>>& node, int k)
{
	int l = node -> left_ ? node -> left_ -> data_ + 1 : 0;
	int r = node -> right_ ? node -> right_ -> data_ + 1: 0;

	if (k == l) 
		return node -> c_;

	if (k > l) {
		assert(node -> right_);
		return kth_inorder(node -> right_, k - l - 1);
	}  else {
		assert(k < l);
		assert(node -> left_);
		return kth_inorder(node -> left_, k);
	}
}

int main(int argc, char const *argv[])
{
	build1();
	std::cout << kth_inorder(root, 0) << std::endl;
	std::cout << kth_inorder(root, 1) << std::endl;
	std::cout << kth_inorder(root, 2) << std::endl;
	std::cout << kth_inorder(root, 3) << std::endl;
	std::cout << kth_inorder(root, 4) << std::endl;
	std::cout << kth_inorder(root, 5) << std::endl;
	std::cout << kth_inorder(root, 6) << std::endl;
	std::cout << kth_inorder(root, 7) << std::endl;
	std::cout << kth_inorder(root, 8) << std::endl;
	std::cout << kth_inorder(root, 9) << std::endl;
	std::cout << kth_inorder(root, 10) << std::endl;
	std::cout << kth_inorder(root, 11) << std::endl;
	std::cout << kth_inorder(root, 12) << std::endl;
	std::cout << kth_inorder(root, 13) << std::endl;
	std::cout << kth_inorder(root, 14) << std::endl;
	std::cout << kth_inorder(root, 15) << std::endl;
	return 0;
}