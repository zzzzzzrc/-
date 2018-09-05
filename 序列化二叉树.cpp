#include<iostream>
#include<vector>
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

void preorder(BinaryTreeNode* root, vector<int> & nums)
{
	if (!root) {
		nums.push_back(-1);
		return;
	}
	else {
		nums.push_back(root->value);
		preorder(root->left,nums);
		preorder(root->right,nums);
		return;
	}
}


vector<int> serialize(BinaryTreeNode* root)
{
	vector<int> output = {};
	if (!root) {
		return output;
	}
	preorder(root, output);
	return output;
}

void recon_core(BinaryTreeNode* cur_node, int & index, vector<int> nums, int l_r = 0)
{
	if (nums[index] == -1)
	{
		if (l_r == 0)
		{
			cur_node->left = NULL;
		}
		else
		{
			cur_node->right = NULL;
		}
		return;
	}
	else
	{
		BinaryTreeNode* node;
		node = new BinaryTreeNode(nums[index]);
		if (l_r == 0) {
			cur_node->left = node;
		}
		else {
			cur_node->right = node;
		}
		cur_node = node;
		index++;
		recon_core(node, index, nums, 0);
		recon_core(node, index, nums, 1);
		return;
	}
}

//根据序列重建  序列中-1为nullptr
BinaryTreeNode* recon(vector<int> nums)
{
	if (nums.size() == 0) {
		return nullptr;
	}
	else
	{
		BinaryTreeNode* root;
		root = new BinaryTreeNode(nums[0]);
		int index = 1;
		recon_core(root, index, nums, 0);
		return root;
	}
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
	vector<int> output = serialize(a);
	//for (int i = 0; i < output.size(); i++)
	//{
	//	cout << output[i] << endl;
	//}
	BinaryTreeNode* root = recon(output);
	cout << root->left->left->value << endl;
	return 0;
}