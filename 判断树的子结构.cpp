#include<iostream>
using namespace std;

struct BinaryTreeNode {
	int value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(int x) { value = x; left = NULL; right = NULL; }
};

bool func(BinaryTreeNode* root1, BinaryTreeNode* root2)  //�ж��Ƿ����ӽṹ
{
	if (root2 == nullptr)   //root2Ϊ��  ����root1�Ƿ�Ϊ�� 2����1 ���ӽṹ
	{
		return true;
	}
	if (root1 == nullptr) {   //2��Ϊ�� 1Ϊ��  �����ӽṹ
		return false;
	}
	if (root1->value != root2->value) {   //����Ϊ��ʱ����ǰ�ڵ��ֵ����  �����ӽṹ
		return false;
	}
	return func(root1->left, root2->left) && func(root1->right, root2->right);  //��ǰ�ڵ��ֵ���  �ֱ��ж���������������
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
			if (rootA->value == rootB->value) {   //��ǰ���ڵ�ֵ���
				output = func(rootA, rootB);      //������  �ж��Ƿ����ӽṹ  ����� output��Ϊfalse
			}
			if (!output) {                        //false 1.��һ�����ڵ��ֵ����  2.��һ�����ڵ��ֵ��ȵ��ǲ������ӽṹ
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