#include <iostream>
#include <memory>
#include <vector>
#include <stack>

template <typename T1, typename T2>
struct BSTNode 
{
	T1 data1;
	T2 data2;

	std::unique_ptr<BSTNode<T1, T2>> left;
	std::unique_ptr<BSTNode<T1, T2>> right;
};

void print(std::unique_ptr<BSTNode<int, char>>& n)
{
    if (!n) return ;
    std::cout << n->data1 << std::endl;
    print(n->left);
    print(n->right);
}

void print_inorder(std::unique_ptr<BSTNode<int, char>>& n)
{
	if (!n ) 
		return ;
	std::stack<BSTNode<int, char>*> stack;

	BSTNode<int, char>* cur = n.get();
	while (!stack.empty() || cur) {
		if (cur) {
			stack.push(cur);
			cur = cur -> left.get();
		} else {
			cur = stack.top();
			stack.pop();
            if (cur -> data1 != 0) {
                std::cout << cur -> data1 << std::endl;
            }
			cur = cur -> right.get();
		}
	}
}

std::unique_ptr<BSTNode<int, char>> build_min_height_bst_from_sorted_array(const std::vector<int>& arr, int start, int end)
{
	if (end == start) {
        return std::make_unique<BSTNode<int, char>>();
    }
	std::unique_ptr<BSTNode<int, char>> node = std::make_unique<BSTNode<int, char>>();
	node -> data1 = arr[start + (end - start) / 2];
	node -> data2 = 'x';
    node -> left = std::move(build_min_height_bst_from_sorted_array(arr, start, (start + end) / 2));
    node -> right = std::move(build_min_height_bst_from_sorted_array(arr, (start + end) / 2 + 1, end));
	return node;
}

int main()
{
	std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	auto node = build_min_height_bst_from_sorted_array(arr, 0, arr.size());
	print_inorder(node);
}
