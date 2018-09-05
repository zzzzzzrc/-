#include<iostream>
using namespace std;

struct BinaryTreeNode
{
	int value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(int x)
	{
		value = x;
		left = NULL;
		right = NULL;
	}
};


//中序遍历  每遍历一个node 便把它作为链表的lastnode 
void func(BinaryTreeNode* node, BinaryTreeNode** last_node)
{
	if (!node) {
		return;
	}
	BinaryTreeNode* cur_node = node;
	if (node->left)
	{
		func(node->left, last_node);    //中序遍历  左
	}
	cur_node->left = *last_node;
	if (*last_node) {
		(*last_node)->right = cur_node;     // 根
	}
	*last_node = cur_node;
	if (cur_node->right) {
		func(cur_node->right, last_node);    //右
	}

}

BinaryTreeNode* convertTree(BinaryTreeNode* root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	BinaryTreeNode* cur_node = root;
	BinaryTreeNode* last_node = nullptr;
	func(root, &last_node);   //这里传指针的引用  目的是修改指针指向的node
	while (last_node->left)
	{
		last_node = last_node->left;
	}
	return last_node;
}

int main()
{
	BinaryTreeNode* a;
	a = new BinaryTreeNode(10);
	BinaryTreeNode* b;
	b = new BinaryTreeNode(5);
	BinaryTreeNode* c;
	c = new BinaryTreeNode(12);
	BinaryTreeNode* d;
	d = new BinaryTreeNode(4);
	BinaryTreeNode* e;
	e = new BinaryTreeNode(7);
	a->left = b;
	a->right = c;
	b->left = d;
	b->right = e;
	BinaryTreeNode* root = convertTree(a);
	while (root->right)
	{
		cout << root->value << endl;
		root = root->right;
	}
	while(root)
	{
		cout << root->value << endl;
		root = root->left;
	}
	return 0;
}