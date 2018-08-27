#include<iostream>
using namespace std;

struct BinaryTreeNode {
	int value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(int x) { value = x; left = NULL; right = NULL; }
};

bool func(BinaryTreeNode* root1, BinaryTreeNode* root2)  //判断是否是子结构
{
	if (root2 == nullptr)   //root2为空  无论root1是否为空 2都是1 的子结构
	{
		return true;
	}
	if (root1 == nullptr) {   //2不为空 1为空  不是子结构
		return false;
	}
	if (root1->value != root2->value) {   //都不为空时，当前节点的值不等  不是子结构
		return false;
	}
	return func(root1->left, root2->left) && func(root1->right, root2->right);  //当前节点的值相等  分别判断左子树和右子树
}

bool isSubTree(BinaryTreeNode* rootA, BinaryTreeNode* rootB)
{
	if (rootA == nullptr) {
		return false;
	}
	else if (rootB == nullptr)
	{
		return true;
	}
	else
	{
		bool output = false;
		if (rootA && rootB) {   
			if (rootA->value == rootB->value) {   //当前根节点值相等
				output = func(rootA, rootB);      //如果相等  判断是否是子结构  不相等 output仍为false
			}
			if (!output) {                        //false 1.上一个根节点的值不等  2.上一个根节点的值相等但是不存在子结构
				output = isSubTree(rootA->left, rootB);
			}
			if (!output) {
				output = isSubTree(rootA->right, rootB);
			}
			
		}
		return output;
	}
}
int main()
{
	BinaryTreeNode* a;
	a = new BinaryTreeNode(1);
	BinaryTreeNode* b;
	b = new BinaryTreeNode(2);
	BinaryTreeNode* c;
	c = new BinaryTreeNode(3);
	BinaryTreeNode* d;
	d = new BinaryTreeNode(4);
	a->left = b;
	b->left = c;
	b->right = d;
	BinaryTreeNode* a1;
	a1 = new BinaryTreeNode(2);
	BinaryTreeNode* b1;
	b1 = new BinaryTreeNode(4);
	BinaryTreeNode* c1;
	c1 = new BinaryTreeNode(1);
	//a1->left = b1;
	a1->right = b1;
	bool output = isSubTree(a, a1);
	cout << output << endl;
	return 0;
}