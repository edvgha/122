#include <vector>
#include "Tree.hpp"

std::unique_ptr<BinaryTreeNode<char>> reconstrut(std::vector<char>& inorder, std::vector<char>& preorder)
{
	if (inorder.empty() || preorder.empty()) {
		return std::make_unique<BinaryTreeNode<char>>();
	}

	auto n = std::make_unique<BinaryTreeNode<char>>();
	n -> data_ = 0;
	n -> c_ = preorder[0];
	//std::cout << n -> c_ << ' ' << preorder[0] << std::endl;

	size_t i = 0;
	for (; i < inorder.size(); ++i) {
		if (preorder[0] == inorder[i]) 
			break;
	}
	std::vector<char> inorderleft(inorder.begin(), inorder.begin() + i);
	std::vector<char> inorderright(inorder.begin() + i + 1, inorder.end());
	preorder.erase(preorder.begin());
	n -> left_ = std::move(reconstrut(inorderleft, preorder));
	n -> right_ = std::move(reconstrut(inorderright, preorder));
	return n;
}

int main()
{
	std::vector<char> inorder = {'F', 'B', 'A', 'E', 'H', 'C', 'D', 'I', 'G'};
	std::vector<char> preorder = {'H', 'B', 'F', 'E', 'A', 'C', 'D', 'G', 'I'};
	auto root = reconstrut(inorder, preorder);
	displayc(root);
}