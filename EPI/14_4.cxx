#include <iostream>
#include <memory>
#include <stack>
#include <queue>

template <typename T1, typename T2>
struct BSTNode 
{
	T1 data1;
	T2 data2;

	std::unique_ptr<BSTNode<T1, T2>> left;
	std::unique_ptr<BSTNode<T1, T2>> right;
};

std::unique_ptr<BSTNode<int, char>> root;

void build()
{
	std::unique_ptr<BSTNode<int, char>> a = std::make_unique<BSTNode<int, char>>();
	a -> data1 = 19;
	a -> data2 = 'a';
	std::unique_ptr<BSTNode<int, char>> b = std::make_unique<BSTNode<int, char>>();
	b -> data1 = 7;
	b -> data2 = 'b';
	std::unique_ptr<BSTNode<int, char>> c = std::make_unique<BSTNode<int, char>>();
	c -> data1 = 3;
	c -> data2 = 'c';
	std::unique_ptr<BSTNode<int, char>> d = std::make_unique<BSTNode<int, char>>();
	d -> data1 = 2;
	d -> data2 = 'd';
	std::unique_ptr<BSTNode<int, char>> e = std::make_unique<BSTNode<int, char>>();
	e -> data1 = 5;
	e -> data2 = 'e';
	std::unique_ptr<BSTNode<int, char>> f = std::make_unique<BSTNode<int, char>>();
	f -> data1 = 11;
	f -> data2 = 'f';
	std::unique_ptr<BSTNode<int, char>> g = std::make_unique<BSTNode<int, char>>();
	g -> data1 = 17;
	g -> data2 = 'g';
	std::unique_ptr<BSTNode<int, char>> h = std::make_unique<BSTNode<int, char>>();
	h -> data1 = 13;
	h -> data2 = 'h';
	std::unique_ptr<BSTNode<int, char>> i = std::make_unique<BSTNode<int, char>>();
	i -> data1 = 43;
	i -> data2 = 'i';
	std::unique_ptr<BSTNode<int, char>> j = std::make_unique<BSTNode<int, char>>();
	j -> data1 = 23;
	j -> data2 = 'j';
	std::unique_ptr<BSTNode<int, char>> k = std::make_unique<BSTNode<int, char>>();
	k -> data1 = 37;
	k -> data2 = 'k';
	std::unique_ptr<BSTNode<int, char>> l = std::make_unique<BSTNode<int, char>>();
	l -> data1 = 29;
	l -> data2 = 'l';
	std::unique_ptr<BSTNode<int, char>> n = std::make_unique<BSTNode<int, char>>();
	n -> data1 = 41;
	n -> data2 = 'n';
	std::unique_ptr<BSTNode<int, char>> m = std::make_unique<BSTNode<int, char>>();
	m -> data1 = 31;
	m -> data2 = 'm';
	std::unique_ptr<BSTNode<int, char>> o = std::make_unique<BSTNode<int, char>>();
	o -> data1 = 47;
	o -> data2 = 'o';
	std::unique_ptr<BSTNode<int, char>> p = std::make_unique<BSTNode<int, char>>();
	p -> data1 = 53;
	p -> data2 = 'p';

	c -> left = std::move(d);
	c -> right = std::move(e);
	g -> left = std::move(h);
	f -> right = std::move(g);
	b -> left = std::move(c);
	b -> right = std::move(f);
	a -> left = std::move(b);
	l -> right = std::move(m);
	k -> right = std::move(n);
	k -> left = std::move(l);
	j -> right = std::move(k);
	o -> right = std::move(p);
	i -> left = std::move(j);
	i -> right = std::move(o);
	a -> right = std::move(i);
	root = std::move(a);
}

void print(std::unique_ptr<BSTNode<int, char>>& n)
{
	if (!n)
		return ;
	std::cout << "(" << n -> data1 << ", " << n -> data2 << ")" << std::endl;
	print(n -> left);
	print(n -> right);
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
			std::cout << cur -> data1 << std::endl;
			cur = cur -> right.get();
		}
	}
}

void LCA(const std::unique_ptr<BSTNode<int, char>>& node, const std::unique_ptr<BSTNode<int, char>>& a, const std::unique_ptr<BSTNode<int, char>>& b)
{
	if (node->data1 == a->data1 || node->data1 == b->data1) {
		std::cout << "(" << node->data1 << ", " << node->data2 << ")" << std::endl;
		return ;
	}
	if (node->data1 > a->data1 && node->data1 < b->data1 && a->data1 < b->data1) {
		std::cout << "(" << node->data1 << ", " << node->data2 << ")" << std::endl;
		return ;
	}
	if (node->data1 > b->data1 && node->data1 < a->data1 && b->data1 < a->data1) {
		std::cout << "(" << node->data1 << ", " << node->data2 << ")" << std::endl;
		return ;
	}

	if (a->data1 < node->data1 && b->data1 < node->data1 && node->left)
		return LCA(node->left, a, b);

	if (a->data1 > node->data1 && b->data1 > node->data1 && node->right)
		return LCA(node->right, a, b);
}


int main()
{
	build();
	//print_inorder(root);
	LCA(root, root->left->left->left, root);
}