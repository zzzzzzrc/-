#include<iostream>
#include "stack.h"
#include "queue.h"
using namespace std;
#define max(a,b) ((a>b)?a:b)

//���ڵ���
template<typename T>
class TreeNode {
public:
	T data;
	TreeNode<T>* parent;
	TreeNode<T>* left_child;
	TreeNode<T>* right_child;
	int height;
	TreeNode() {};
	TreeNode(T value, TreeNode<T>* p = NULL, TreeNode<T>* l=NULL, TreeNode<T>* r=NULL, int h = 0) { //���캯��
		data = value;
		parent = p;
		left_child = l;
		right_child = r;
		height = h;
	}
	//�����ӿ�
	//int size();//ͳ�Ƶ�ǰ�ڵ���������������Ϊ����������ģ��
	TreeNode<T>* insertAsLeftChild(T const& value);
	TreeNode<T>* insertAsRightChild(T const& value);
	//TreeNode<T>* succ(); //��ǰ�ڵ��ֱ�Ӻ��
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
//������ڵ�ĸ߶�
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

//��������
template<typename T>
class BinTree {
public:
	int _size;
	TreeNode<T>* _root;
	BinTree(int size = 0, TreeNode<T>* p = NULL) { //���캯�� ��ʼ��ģΪ0 ���ڵ�Ϊnull
		_size = size;
		_root = p;
	}
	/*~BinTree() {
		if (_size > 0) {
			remove(_root);
		}
	}*/
	//��Ա����
	int get_size() { return _size; }
	TreeNode<T>* insertAsRoot(T const & value); //��Ϊ���ڵ����
	TreeNode<T>* insertAsLeft(T const & value, TreeNode<T>* p); //��Ϊ�ڵ�p�����Ӳ���
	TreeNode<T>* insertAsRight(T const & value, TreeNode<T>* p); // ��Ϊ�ڵ�p���Һ��Ӳ���
	int updateHeight(TreeNode<T>* p); //���½ڵ�p�ĸ߶�
	void updateHeightAbove(TreeNode<T>* p); //���½ڵ�p����ͨ·�ĸ߶�
	TreeNode<T>* attachAsLeftChild(TreeNode<T>* p, BinTree<T> T); //��������T��Ϊp������������
	TreeNode<T>* attachAsRightChild(TreeNode<T>* p, BinTree<T> T); //��������T��Ϊp������������
	TreeNode<T>* remove(TreeNode<T>* p); //�Ƴ�p�ڵ㼰������
	int get_subtree_size(TreeNode<T>* p); //�õ��Խڵ�pΪ���������Ĺ�ģ
	void visit(TreeNode<T>* p);
	void Traverse_preorder(TreeNode<T>* p); //����
	void Traverse_inorder(TreeNode<T>* p); //����
	void Traverse_postorder(TreeNode<T>* p); //����
	void preorder(TreeNode<T>* p); //���� ������
	void left_preorder(TreeNode<T>* p, Stack<TreeNode<T>*> &s);
	void inorder(TreeNode<T>* p); //���� ������
	void left_inorder(TreeNode<T>* p, Stack<TreeNode<T>*> &s);
	void postorder(TreeNode<T>* p);// ���� ������
	void left_postorder(Stack<TreeNode<T>*> &s);
	void Traverse_level(TreeNode<T>* p); //��α���
};

//���½ڵ�p�ĸ߶�
template<typename T>
int BinTree<T>::updateHeight(TreeNode<T>* p) {
	p->height = 1 + max(p->left_child->get_height(), p->right_child->get_height());
	return p->height;
}
//���½ڵ�p����ͨ·�ĸ߶�
template<typename T>
void BinTree<T>::updateHeightAbove(TreeNode<T>* p) {
	while (p) {
		updateHeight(p); //���µ�ǰ�ڵ�
		p = p->parent;   //���ϻ���ֱ�����ڵ�  ���ڵ��paernt==NULL
	}
}

//������ڵ�
template<typename T>
TreeNode<T>* BinTree<T>::insertAsRoot(T const& value) {
	TreeNode<T>* root_node = new TreeNode<T>;
	root_node->data = value;
	_root = root_node;
	_size = 1;
	return _root;
}
//��Ϊ�ڵ�p�����Ӳ���
template<typename T>
TreeNode<T>* BinTree<T>::insertAsLeft(T const & value, TreeNode<T>* p) {
	_size++;
	p->insertAsLeftChild(value);
	updateHeightAbove(p);
	return p->left_child;
}
//��Ϊ�ڵ�p���Һ��Ӳ���
template<typename T>
TreeNode<T>* BinTree<T>::insertAsRight(T const & value, TreeNode<T>* p) {
	_size++;
	p->insertAsRightChild(value);
	updateHeightAbove(p);
	return p->right_child;
}
//��������T��Ϊp������������  T�����ÿ�
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
//��������T��Ϊp������������
template<typename T>
TreeNode<T>* BinTree<T>::attachAsRightChild(TreeNode<T>* p, BinTree<T> T) {
	p->right_child = T._root;
	p->right_child->parent = p;
	updateHeightAbove(p);
	_size = _size + T._size;
	return p;
}
//�Ƴ�ĳ�ڵ㼰������
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
//�����ڵ�
template<typename T>
void BinTree<T>::visit(TreeNode<T>* p) {
	cout << p->data << endl;
}
//������� �ݹ�汾
template<typename T>
void BinTree<T>::Traverse_preorder(TreeNode<T>* p) {
	if (!p) {
		return;
	}
	visit(p);
	Traverse_preorder(p->left_child);
	Traverse_preorder(p->right_child);
}
//������� �ݹ�汾
template<typename T>
void BinTree<T>::Traverse_inorder(TreeNode<T>* p) {
	if (!p) {
		return;
	}
	Traverse_inorder(p->left_child);
	visit(p);
	Traverse_inorder(p->right_child);
}
//������� �ݹ�汾
template<typename T>
void BinTree<T>::Traverse_postorder(TreeNode<T>* p) {
	if (!p) {
		return;
	}
	Traverse_postorder(p->left_child);
	Traverse_postorder(p->right_child);
	visit(p);
}
//������� �����汾
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
//������� �����汾
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
//������� �����汾
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
//��α���
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

/*-----------------------������------------------------*/
int main() {
	/*TreeNode<int> root(1);
	cout << root.left_child->get_height() << endl;
	root.insertAsLeftChild(2);
	cout << root.left_child->get_height() << endl;
	root.insertAsRightChild(3);
	cout << root.data << root.left_child->data << root.right_child->data << endl;*/
	//����һ��������
	BinTree<int> test_tree;
	test_tree.insertAsRoot(1);
	test_tree.insertAsLeft(2,test_tree._root);
	BinTree<int> test_tree1;
	test_tree1.insertAsRoot(3);
	test_tree1.insertAsLeft(4, test_tree1._root);
	test_tree1.insertAsRight(5, test_tree1._root);
	test_tree.attachAsRightChild(test_tree._root, test_tree1);
	cout << "preorder �ݹ�:" << endl;
	test_tree.Traverse_preorder(test_tree._root);
	cout << "preorder ����:" << endl;
	test_tree.preorder(test_tree._root);
	cout << "inorder �ݹ�:" << endl;
	test_tree.Traverse_inorder(test_tree._root);
	cout << "inorder ����:" << endl;
	test_tree.inorder(test_tree._root);
	cout << "postorder �ݹ�:" << endl;
	test_tree.Traverse_postorder(test_tree._root);
	cout << "postorder ����:" << endl;
	test_tree.postorder(test_tree._root);
	cout << "��α���:" << endl;
	test_tree.Traverse_level(test_tree._root);
	cout << "tree size: "<< test_tree._size << endl;
	//cout << test_tree._root->height << endl;
	//cout << test_tree._root->right_child->data << endl;
	test_tree.remove(test_tree._root->right_child);
	cout << "tree size: " << test_tree._size << endl;

	return 0;
}