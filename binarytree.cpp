#include<iostream>
using namespace std;

struct BinaryTreeNode {
	int value;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
}; 


BinaryTreeNode* fun(int *preorder, int* midorder, int length, int pstart, int pend, int mstart, int mend)
{
	cout << "length:"<<length<<" pstart:" << pstart <<" pend:"<<pend<< " mstart" << mstart <<" mend"<<mend<< endl;
	if (preorder == nullptr || midorder == nullptr || length == 0) {
		return nullptr;
	}
	/*if (length == 1) {
		BinaryTreeNode* root = new BinaryTreeNode();
		root->value = preorder[0];
		root->left = nullptr;
		root->right = nullptr;
		return root;
	}*/
	BinaryTreeNode* root = new BinaryTreeNode();
	root->value = preorder[pstart];
	root->left = nullptr;
	root->right = nullptr;
	int i = mstart;
	while (true)
	{
		if (midorder[i] == preorder[pstart]) { break; }
		else { i++; }
	}
	//左右子树的长度（节点个数）
	int left_length = i-pstart;
	int right_length = length-(i-pstart)-1;

	int pre_start_l = pstart+1;
	int pre_end_l = pre_start_l + left_length - 1;
	int mid_start_l = mstart;
	int mid_end_l = mid_start_l + left_length - 1;

	int pre_start_r = pre_end_l+1;
	int pre_end_r = pre_start_r+right_length-1;
	int mid_start_r = i+1;
	int mid_end_r = mend;
	if (i > mstart) { //有左子树
		root->left = fun(preorder, midorder, left_length, pre_start_l, pre_end_l,mid_start_l,mid_end_l);
	}
	if (i < mend) { //有右子树
		root->right = fun(preorder, midorder, right_length, pre_start_r, pre_end_r, mid_start_r, mid_end_r);
	}
	return root;
}



int main() {
	int preorder[] = { 1,2,4,7,3,5,6,8 };
	int midorder[] = { 4,7,2,1,5,3,8,6 };
	BinaryTreeNode* root = fun(preorder, midorder, 8, 0, 7,0,7);
	cout << root->value << endl;
	return 0;
}