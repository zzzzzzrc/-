#include<iostream>
#include "stack.h"
#include "queue.h"
using namespace std;
#define max(a,b) ((a>b)?a:b)

//树节点类
template<typename T>
class TreeNode {
public:
	T data;
	TreeNode<T>* parent;
	TreeNode<T>* left_child;
	TreeNode<T>* right_child;
	int height;
	TreeNode() {};
	TreeNode(T value, TreeNode<T>* p = NULL, TreeNode<T>* l=NULL, TreeNode<T>* r=NULL, int h = 0) { //构造函数
		data = value;
		parent = p;
		left_child = l;
		right_child = r;
		height = h;
	}
	//操作接口
	//int size();//统计当前节点后代总数，（以其为根的子树规模）
	TreeNode<T>* insertAsLeftChild(T const& value);
	TreeNode<T>* insertAsRightChild(T const& value);
	//TreeNode<T>* succ(); //当前节点的直接后继
	bool IsRoot() { return !(this->parent); }
	bool IsLeftChild() { return (this->parent)&&(this->parent->left_child == this); }
	bool IsRightChild() { return (this->parent) && (this->parent->right_child == this); }
	bool HasParent() { return (this->parent); }
	bool HasLeftChild() { return (this->left_child); }
	bool HasRightChild() { return (this->right_child); }
	bool HasBothChild() { return (this->left_child) && (this->right_child); }
	bool HasChild() { return(this->left_child) || (this->right_child); }
	bool IsLeaf() { return !(this->HasChild); }
	int get_height();
};
//获得树节点的高度
template<typename T>
int TreeNode<T>::get_height() {
	if (this) {
		return height;
	}
	else {
		return -1;
	}
}
template<typename T>
TreeNode<T>* TreeNode<T>::insertAsLeftChild(T const&value) {
	if (!this->left_child) {
		TreeNode<T>* new_node = new TreeNode<T>;
		new_node->data = value;
		new_node->parent = this;
		left_child = new_node;
		return new_node;
	}
	else {
		cout << "left child has exist" << endl;
		return left_child;
	}
}
template<typename T>
TreeNode<T>* TreeNode<T>::insertAsRightChild(T const&value) {
	if (!this->right_child) {
		TreeNode<T>* new_node = new TreeNode<T>;
		new_node->data = value;
		new_node->parent = this;
		right_child = new_node;
		return new_node;
	}
	else {
		cout << "right child has exist" << endl;
		return right_child;
	}
}

//二叉树类
template<typename T>
class BinTree {
public:
	int _size;
	TreeNode<T>* _root;
	BinTree(int size = 0, TreeNode<T>* p = NULL) { //构造函数 初始规模为0 根节点为null
		_size = size;
		_root = p;
	}
	/*~BinTree() {
		if (_size > 0) {
			remove(_root);
		}
	}*/
	//成员函数
	int get_size() { return _size; }
	TreeNode<T>* insertAsRoot(T const & value); //作为根节点插入
	TreeNode<T>* insertAsLeft(T const & value, TreeNode<T>* p); //作为节点p的左孩子插入
	TreeNode<T>* insertAsRight(T const & value, TreeNode<T>* p); // 作为节点p的右孩子插入
	int updateHeight(TreeNode<T>* p); //更新节点p的高度
	void updateHeightAbove(TreeNode<T>* p); //更新节点p向上通路的高度
	TreeNode<T>* attachAsLeftChild(TreeNode<T>* p, BinTree<T> T); //将二叉树T作为p的左子树插入
	TreeNode<T>* attachAsRightChild(TreeNode<T>* p, BinTree<T> T); //将二叉树T作为p的右子树插入
	TreeNode<T>* remove(TreeNode<T>* p); //移除p节点及其子树
	int get_subtree_size(TreeNode<T>* p); //得到以节点p为根的子树的规模
	void visit(TreeNode<T>* p);
	void Traverse_preorder(TreeNode<T>* p); //先序
	void Traverse_inorder(TreeNode<T>* p); //中序
	void Traverse_postorder(TreeNode<T>* p); //后序
	void preorder(TreeNode<T>* p); //先序 迭代版
	void left_preorder(TreeNode<T>* p, Stack<TreeNode<T>*> &s);
	void inorder(TreeNode<T>* p); //中序 迭代版
	void left_inorder(TreeNode<T>* p, Stack<TreeNode<T>*> &s);
	void postorder(TreeNode<T>* p);// 后序 迭代版
	void left_postorder(Stack<TreeNode<T>*> &s);
	void Traverse_level(TreeNode<T>* p); //层次遍历
};

//更新节点p的高度
template<typename T>
int BinTree<T>::updateHeight(TreeNode<T>* p) {
	p->height = 1 + max(p->left_child->get_height(), p->right_child->get_height());
	return p->height;
}
//更新节点p向上通路的高度
template<typename T>
void BinTree<T>::updateHeightAbove(TreeNode<T>* p) {
	while (p) {
		updateHeight(p); //更新当前节点
		p = p->parent;   //向上回溯直至根节点  根节点的paernt==NULL
	}
}

//插入根节点
template<typename T>
TreeNode<T>* BinTree<T>::insertAsRoot(T const& value) {
	TreeNode<T>* root_node = new TreeNode<T>;
	root_node->data = value;
	_root = root_node;
	_size = 1;
	return _root;
}
//作为节点p的左孩子插入
template<typename T>
TreeNode<T>* BinTree<T>::insertAsLeft(T const & value, TreeNode<T>* p) {
	_size++;
	p->insertAsLeftChild(value);
	updateHeightAbove(p);
	return p->left_child;
}
//作为节点p的右孩子插入
template<typename T>
TreeNode<T>* BinTree<T>::insertAsRight(T const & value, TreeNode<T>* p) {
	_size++;
	p->insertAsRightChild(value);
	updateHeightAbove(p);
	return p->right_child;
}
//将二叉树T作为p的左子树插入  T本身置空
template<typename T>
TreeNode<T>* BinTree<T>::attachAsLeftChild(TreeNode<T>* p, BinTree<T> T) {
	p->left_child = T._root;
	p->left_child->parent = p;
	updateHeightAbove(p);
	_size = _size + T._size;
	T._root = NULL;
	T._size = 0;
	return p;
}
//将二叉树T作为p的右子树插入
template<typename T>
TreeNode<T>* BinTree<T>::attachAsRightChild(TreeNode<T>* p, BinTree<T> T) {
	p->right_child = T._root;
	p->right_child->parent = p;
	updateHeightAbove(p);
	_size = _size + T._size;
	return p;
}
//移除某节点及其子树
template<typename T>
TreeNode<T>* BinTree<T>::remove(TreeNode<T>* p) {
	if (p->IsLeftChild()) {
		p->parent->left_child = NULL;
		_size = _size - get_subtree_size(p);
	}
	else {
		p->parent->right_child = NULL;
		_size = _size - get_subtree_size(p);
	}
	return p;
}
template<typename T>
int BinTree<T>::get_subtree_size(TreeNode<T>* p) {
	if (!p) {
		return 0;
	}
	else {
		while (p) {
			return 1 + get_subtree_size(p->left_child) + get_subtree_size(p->right_child);
		}
	}
}
//遍历节点
template<typename T>
void BinTree<T>::visit(TreeNode<T>* p) {
	cout << p->data << endl;
}
//先序遍历 递归版本
template<typename T>
void BinTree<T>::Traverse_preorder(TreeNode<T>* p) {
	if (!p) {
		return;
	}
	visit(p);
	Traverse_preorder(p->left_child);
	Traverse_preorder(p->right_child);
}
//中序遍历 递归版本
template<typename T>
void BinTree<T>::Traverse_inorder(TreeNode<T>* p) {
	if (!p) {
		return;
	}
	Traverse_inorder(p->left_child);
	visit(p);
	Traverse_inorder(p->right_child);
}
//后序遍历 递归版本
template<typename T>
void BinTree<T>::Traverse_postorder(TreeNode<T>* p) {
	if (!p) {
		return;
	}
	Traverse_postorder(p->left_child);
	Traverse_postorder(p->right_child);
	visit(p);
}
//先序遍历 迭代版本
template<typename T>
void BinTree<T>::left_preorder(TreeNode<T>* p, Stack<TreeNode<T>*> &s) {
	while (p) {
		visit(p);
		if (p->HasRightChild()) {
			s.push(p->right_child);
		}
		p = p->left_child;
	}
}
template<typename T>
void BinTree<T>::preorder(TreeNode<T>* p) {
	Stack<TreeNode<T>*> S;
	while (true) {
		left_preorder(p, S);
		if (S._size == 0) {
			break;
		}
		p = S.pop();
	}
}
//中序遍历 迭代版本
template<typename T>
void BinTree<T>::left_inorder(TreeNode<T>* p, Stack<TreeNode<T>*> &s) {
	while (p) {
		s.push(p);
		p = p->left_child;
	}
}
template<typename T>
void BinTree<T>::inorder(TreeNode<T>* p) {
	Stack<TreeNode<T>*> S;
	while (true) {
		left_inorder(p, S);
		if (S._size == 0) {
			break;
		}
		p = S.pop();
		visit(p);
		p = p->right_child;
	}
}
//后序遍历 迭代版本
template<typename T>
void BinTree<T>::left_postorder(Stack<TreeNode<T>*> &s) {
	TreeNode<T>* p = s.top();
	while (p) {
		if (p->HasLeftChild()) {
			if (p->HasRightChild()) {
				s.push(p->right_child);
			}
			s.push(p->left_child);
		}
		else {
			s.push(p->right_child);
		}
		p = s.top();
	}
	s.pop();
}
template<typename T>
void BinTree<T>::postorder(TreeNode<T>* p) {
	Stack<TreeNode<T>*> S;
	S.push(p);
	while (S._size != 0) {
		if (S.top() != p->parent) {
			left_postorder(S);
		}
		p = S.pop();
		visit(p);
	}
}
//层次遍历
template<typename T>
void BinTree<T>::Traverse_level(TreeNode<T>* p) {
	Queue<TreeNode<T>*> queue;
	queue.enqueue(p);
	int count = 0;
	while (count < _size) {
		TreeNode<T>* q = queue.dequeue()->data;
		visit(q);
		if (q->HasLeftChild()) {
			queue.enqueue(q->left_child);
			//cout << "in: " << q->left_child->data << endl;
		}
		if (q->HasRightChild()) {
			queue.enqueue(q->right_child);
			//cout << "in: " << q->right_child->data << endl;
		}
		//cout << "out:" << queue.header->succ->data->data << endl;
		count++;
	}
}

/*-----------------------主函数------------------------*/
int main() {
	/*TreeNode<int> root(1);
	cout << root.left_child->get_height() << endl;
	root.insertAsLeftChild(2);
	cout << root.left_child->get_height() << endl;
	root.insertAsRightChild(3);
	cout << root.data << root.left_child->data << root.right_child->data << endl;*/
	//构建一个二叉树
	BinTree<int> test_tree;
	test_tree.insertAsRoot(1);
	test_tree.insertAsLeft(2,test_tree._root);
	BinTree<int> test_tree1;
	test_tree1.insertAsRoot(3);
	test_tree1.insertAsLeft(4, test_tree1._root);
	test_tree1.insertAsRight(5, test_tree1._root);
	test_tree.attachAsRightChild(test_tree._root, test_tree1);
	cout << "preorder 递归:" << endl;
	test_tree.Traverse_preorder(test_tree._root);
	cout << "preorder 迭代:" << endl;
	test_tree.preorder(test_tree._root);
	cout << "inorder 递归:" << endl;
	test_tree.Traverse_inorder(test_tree._root);
	cout << "inorder 迭代:" << endl;
	test_tree.inorder(test_tree._root);
	cout << "postorder 递归:" << endl;
	test_tree.Traverse_postorder(test_tree._root);
	cout << "postorder 迭代:" << endl;
	test_tree.postorder(test_tree._root);
	cout << "层次遍历:" << endl;
	test_tree.Traverse_level(test_tree._root);
	cout << "tree size: "<< test_tree._size << endl;
	//cout << test_tree._root->height << endl;
	//cout << test_tree._root->right_child->data << endl;
	test_tree.remove(test_tree._root->right_child);
	cout << "tree size: " << test_tree._size << endl;

	return 0;
}