#include <iostream>
#include <memory>

template <typename T>
struct BinaryTreeNode 
{
	T data_;
	char c_;
	std::unique_ptr<BinaryTreeNode<T>> left_;
	std::unique_ptr<BinaryTreeNode<T>> right_;
};

std::unique_ptr<BinaryTreeNode<int>> root;

void build()
{
	auto A = std::make_unique<BinaryTreeNode<int>>();
	A -> data_ = 314;
	A -> c_ = 'A';
	auto B = std::make_unique<BinaryTreeNode<int>>();
	B -> data_ = 6;
	B -> c_ = 'B';
	auto I = std::make_unique<BinaryTreeNode<int>>();
	I -> data_ = 6;
	I -> c_ = 'I';
	auto C = std::make_unique<BinaryTreeNode<int>>();
	C -> data_ = 271;
	C -> c_ = 'C';
	auto F = std::make_unique<BinaryTreeNode<int>>();
	F -> data_ = 561;
	F -> c_ = 'F';
	auto J = std::make_unique<BinaryTreeNode<int>>();
	J -> data_ = 2;
	J -> c_ = 'J';
	auto O = std::make_unique<BinaryTreeNode<int>>();
	O -> data_ = 271;
	O -> c_ = 'O';
	auto D = std::make_unique<BinaryTreeNode<int>>();
	D -> data_ = 28;
	D -> c_ = 'D';
	auto E = std::make_unique<BinaryTreeNode<int>>();
	E -> data_ = 0;
	E -> c_ = 'E';
	auto G = std::make_unique<BinaryTreeNode<int>>();
	G -> data_ = 3;
	G -> c_ = 'G';
	auto K = std::make_unique<BinaryTreeNode<int>>();
	K -> data_ = 1;
	K -> c_ = 'K';
	auto P = std::make_unique<BinaryTreeNode<int>>();
	P -> data_ = 28;
	P -> c_ = 'P';
	auto H = std::make_unique<BinaryTreeNode<int>>();
	H -> data_ = 17;
	H -> c_ = 'H';
	auto L = std::make_unique<BinaryTreeNode<int>>();
	L -> data_ = 401;
	L -> c_ = 'L';
	auto N = std::make_unique<BinaryTreeNode<int>>();
	N -> data_ = 257;
	N -> c_ = 'N';
	auto M = std::make_unique<BinaryTreeNode<int>>();
	M -> data_ = 641;
	M -> c_ = 'M';

	L -> right_ = std::move(M);
	K -> left_ = std::move(L);
	K -> right_ = std::move(N);
	G -> left_ = std::move(H);
	C -> left_ = std::move(D);
	C -> right_ = std::move(E);
	F -> right_ = std::move(G);
	J -> right_ = std::move(K);
	O -> right_ = std::move(P);
	B -> left_ = std::move(C);
	B -> right_ = std::move(F);
	I -> left_ = std::move(J);
	I -> right_ = std::move(O);
	A -> left_ = std::move(B);
	A -> right_ = std::move(I);
	root = std::move(A);

}

void build1()
{
	auto A = std::make_unique<BinaryTreeNode<int>>();
	A -> data_ = 15;
	A -> c_ = 'A';
	auto B = std::make_unique<BinaryTreeNode<int>>();
	B -> data_ = 6;
	B -> c_ = 'B';
	auto I = std::make_unique<BinaryTreeNode<int>>();
	I -> data_ = 7;
	I -> c_ = 'I';
	auto C = std::make_unique<BinaryTreeNode<int>>();
	C -> data_ = 2;
	C -> c_ = 'C';
	auto F = std::make_unique<BinaryTreeNode<int>>();
	F -> data_ = 2;
	F -> c_ = 'F';
	auto J = std::make_unique<BinaryTreeNode<int>>();
	J -> data_ = 4;
	J -> c_ = 'J';
	auto O = std::make_unique<BinaryTreeNode<int>>();
	O -> data_ = 1;
	O -> c_ = 'O';
	auto D = std::make_unique<BinaryTreeNode<int>>();
	D -> data_ = 0;
	D -> c_ = 'D';
	auto E = std::make_unique<BinaryTreeNode<int>>();
	E -> data_ = 0;
	E -> c_ = 'E';
	auto G = std::make_unique<BinaryTreeNode<int>>();
	G -> data_ = 1;
	G -> c_ = 'G';
	auto K = std::make_unique<BinaryTreeNode<int>>();
	K -> data_ = 3;
	K -> c_ = 'K';
	auto P = std::make_unique<BinaryTreeNode<int>>();
	P -> data_ = 0;
	P -> c_ = 'P';
	auto H = std::make_unique<BinaryTreeNode<int>>();
	H -> data_ = 0;
	H -> c_ = 'H';
	auto L = std::make_unique<BinaryTreeNode<int>>();
	L -> data_ = 1;
	L -> c_ = 'L';
	auto N = std::make_unique<BinaryTreeNode<int>>();
	N -> data_ = 0;
	N -> c_ = 'N';
	auto M = std::make_unique<BinaryTreeNode<int>>();
	M -> data_ = 0;
	M -> c_ = 'M';

	L -> right_ = std::move(M);
	K -> left_ = std::move(L);
	K -> right_ = std::move(N);
	G -> left_ = std::move(H);
	C -> left_ = std::move(D);
	C -> right_ = std::move(E);
	F -> right_ = std::move(G);
	J -> right_ = std::move(K);
	O -> right_ = std::move(P);
	B -> left_ = std::move(C);
	B -> right_ = std::move(F);
	I -> left_ = std::move(J);
	I -> right_ = std::move(O);
	A -> left_ = std::move(B);
	A -> right_ = std::move(I);
	root = std::move(A);
}

template <typename T>
void display(std::unique_ptr<BinaryTreeNode<T>>& n)
{
	if (! n ) return;
	std::cout << n -> data_ << std::endl;
	display(n -> left_);
	display(n -> right_);
}

template <typename T>
void displayc(std::unique_ptr<BinaryTreeNode<T>>& n)
{
	if (!n ) return;
	if (n && n -> c_ == char()) return ;
	std::cout << n -> c_ << std::endl;
	displayc(n -> left_);
	displayc(n -> right_);
}