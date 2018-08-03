#include <iostream>
#include <typeinfo>
using namespace std;


/*-----------------------------列表节点类--------------------------------*/
template<typename T> 
struct ListNode {
	//数据成员
	T data;
	ListNode<T>* pred; //指向ListNode类型的指针
	ListNode<T>* succ;
	ListNode() {};   //声明构造函数
	//构造函数
	ListNode(T value, ListNode<T>* p = NULL, ListNode<T>* s = NULL) {
		data = value;
		pred = p;
		succ = s;
	}
	//成员函数
	ListNode<T>*  insertAsPred(T const& e); //插入当前节点的前驱结点，并返回其位置
	ListNode<T>*  insertAsSucc(T const& e); // 后继节点
};

template<typename T>
ListNode<T>*  ListNode<T>::insertAsPred(T const& e) {
	//ListNode<T> tmp(e); //构造前驱节点
	//tmp.succ = this;    //cur结点的前驱节点的后继节点为cur
	//pred = &tmp;        //cur结点的前驱节点为tmp
	ListNode<T>* tmp = new ListNode<T>;
	tmp->data = e;
	tmp->pred = pred;
	tmp->succ = this;
	if (pred != NULL) {
		pred->succ = tmp; //当前结点的前驱结点 的后继结点为x（原来为当前结点） 此时未改变pred
	}
	pred = tmp; //当前结点的前驱结点为 tmp
	return tmp;
}

template<class T>
ListNode<T>*  ListNode<T>::insertAsSucc(T const& e) {
	//ListNode<T> tmp(e);
	//tmp.pred = this;
	//succ = &tmp;
	ListNode<T>* tmp = new ListNode<T>;
	tmp->data = e;
	tmp->pred = this;
	tmp->succ = succ;
	if (succ != NULL) {
		succ->pred = tmp;
	}
	succ = tmp;
	return tmp;
}

/*---------------------列表类-----------------------------*/
template<class T>
class List {
private:
	//int _size;
	//ListNode<T>* header;
	//ListNode<T>* trailer; //头尾哨兵节点
protected:
	void init();
	//T& operator [](int r);
public:
	int _size;
	List() {
		cout << "start initial" << endl;
		init();
	}
	List(ListNode<T>* p, int n);
	List(List<T> const & L); //复制整体列表L
	List(List<T> const & L, int r, int n); //复制列表L从第r个node开始的n项
	ListNode<T>* operator [](int r); //重载运算符[] 按秩返回
	ListNode<T>* header;
	ListNode<T>* trailer; //头尾哨兵节点
	//ListNode<T>* first;  //首节点
	//ListNode<T>* last;   //末节点
	ListNode<T>* find(T const& value, int n, ListNode<T>* p) const;  //从节点p开始的n个节点内找值为value的节点
	ListNode<T>* insertAsFirst(T const& value); //作为首节点插入列表 data为value 
	ListNode<T>* insertAsLast(T const& value); //作为首节点插入列表 data为value
	ListNode<T>* insertAsPred(ListNode<T>* p, T const& value); //作为p的前驱结点插入
	ListNode<T>* insertAsSucc(ListNode<T>* p, T const& value); //作为p的后继结点插入
	void copynode(ListNode<T>* p, int n); //基于复制的构造
	void show_data();
	T remove(ListNode<T>* p);
	~List();//析构函数
	int clear();//清除列表内所有结点
	int deduplicate();//无序列表去重
	int uniquify(); //有序列表去重
	ListNode<T>* search(T value, int n, ListNode<T>* p); //有序列表的查找
	void insertorder(ListNode<T>* p, int n);//插入排序 p节点前的n个进行排序
	void selectorder(ListNode<T>* p, int n);//选择排序 p节点后的n个进行排序
	ListNode<T>* findmax(ListNode<T>* p, int n);//在节点p后面（包括p）n个节点中找到最大的 若有重复的 选择靠后的
	void mergesort(ListNode<T>* p, int start, int n); //归并排序
	//void merge(int start, int end);
};
//构造函数   初始化List
template<typename T>
void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
	cout << "initial complete!" << endl;
}
//重载运算符 [] 能够按rank返回元素的值
template<typename T>
ListNode<T>* List<T>::operator[](int r) {
	if (r > _size - 1) {
		throw "index error";
	}
	int i = 0;
	ListNode<T>* p = header;
	while (i <= r) {
		p = p->succ;
		i++;
	}
	return p;
}
//节点p之前n个节点中查找值为value的节点
template<typename T>
ListNode<T>* List<T>::find(T const &value, int n, ListNode<T>* p) const{
	while (n > 0 && p->pred) {
		if (p->pred->data == value) {
			return p->pred;
		}
		p = p->pred;
		n--;
	}
	return NULL;
}
//作为首节点插入列表
template<typename T>
ListNode<T>* List<T>::insertAsFirst(T const& value) {
	/*ListNode<T>* tmp = new ListNode<T>;
	tmp->data = value;
	tmp->pred = header;
	header->succ = tmp;*/
	header->insertAsSucc(value);
	_size++;
	return header->succ;
}
//作为尾节点插入列表
template<typename T>
ListNode<T>* List<T>::insertAsLast(T const& value) {
	trailer->insertAsPred(value);
	_size++;
	return trailer->pred;
}
//作为节点p的前驱结点
template<typename T>
ListNode<T>* List<T>::insertAsPred(ListNode<T>* p, T const& value) {
	_size++;
	return p->insertAsPred(value);
}
//作为节点p的后继节点
template<typename T>
ListNode<T>* List<T>::insertAsSucc(ListNode<T>* p, T const& value) {
	_size++;
	return p->insertAsSucc(value);
}
//基于复制的构造
template<typename T>
void List<T>::copynode(ListNode<T>* p, int n) {
	init();
	while (n > 0) {
		insertAsLast(p->data);
		p = p->succ;
		n--;
	}
}
//基于复制的构造方法  从p开始的n个
template<typename T>
List<T>::List(ListNode<T>* p, int n) {
	copynode(p, n);
}
template<typename T> //复制整体L
List<T>::List(List<T> const & L) {
	copynode(L.header.succ, L._size);
}
template<typename T> //复制列表L的第r个开始 共n个
List<T>::List(List<T> const & L, int r, int n) {
	copynode(L[r], n);
}
//打印所有结点的data
template<typename T>
void List<T>::show_data() {
	int i = 0;
	ListNode<T>* p = header->succ;
	while (i < _size) {
		cout << "the num " << i << " node's data is: " << p->data << endl;
		p = p->succ;
		i++;
	}
	cout << "the list size = " << _size << endl;
}
//删除某节点
template<typename T>
T List<T>::remove(ListNode<T>* p) {
	T tmp_data = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return tmp_data;
}
//析构函数
template<typename T>
List<T>::~List() {
	clear(); // 清除列表内所有的node
	delete header;
	delete trailer;
}
template<typename T>
int List<T>::clear() {
	int old_size = _size;
	while (_size > 0) {
		remove(header->succ);
	}
	return old_size;
}
//无序列表的去重
template<typename T>
int List<T>::deduplicate() {
	if (_size < 2) {
		return 0;
	}
	ListNode<T>* p = header;
	int r = 0;
	int oldsize = _size;
	while (p->succ) {
		ListNode<T>* q = find(p->succ->data, r, p->succ);
		if (q != NULL) {
			remove(p->succ);
		}
		else {
			p = p->succ;
			r++;
		}
	}
	return _size - oldsize;
}
//有序列表的去重
template<typename T>
int List<T>::uniquify() {
	if (_size < 2) {
		return 0;
	}
	int oldsize = _size;
	ListNode<T>* p = header;
	while (p->succ->succ != NULL) {
		if (p->succ->data == p->succ->succ->data) {
			remove(p->succ->succ);
		}
		else {
			p = p->succ;
		}
	}
	return oldsize - _size;
}
//有序列表的查找
template<typename T>
ListNode<T>* List<T>::search(T value, int n, ListNode<T>* p) {
	ListNode<T>* m = NULL;
	while (n > 0 && p->pred) {
		if (p->pred->data > value) {
			p = p->pred;
			n--;
		}
		else {
			return p->pred;  //返回不大于value的节点，若要插入节点，则return的节点->succ为插入的节点
		}
	}
	cout << "not found!" << endl;
	return  m; // 抛出异常如何实现？返回左边界
}

//插入排序
template<typename T>
void List<T>::insertorder(ListNode<T>* p, int n) {
	int i = 0;
	ListNode<T>* start = p;
	p = p->succ;
	while (i < n) {
		ListNode<T>* q = search(p->data, i, p);
		if (q != NULL) {
			insertAsSucc(q, p->data);
			//show_data();
			p = p->succ;
			remove(p->pred);
			//show_data(); 
			i++;
		}
		else {
			insertAsSucc(header,p->data);
			//show_data();
			p = p->succ;
			remove(p->pred);
			//show_data();
			i++;
		}
	}
}
//选择排序
template<typename T>
void List<T>::selectorder(ListNode<T>* p, int n) {
	ListNode<T>* end = p;
	int i = n;
	while (i >= 0) {
		end = end->succ;
		i--;
	}
	while (n > 0) {
		ListNode<T>* q = findmax(p->succ, n);
		insertAsPred(end,q->data);
		end = end->pred;
		n--;
		//show_data();
		remove(q);
		//show_data();
	}
}
template<typename T>
ListNode<T>* List<T>::findmax(ListNode<T>* p, int n) {
	ListNode<T>* max = p;
	while (n > 0) {
		if (p->data >= max->data) {
			max = p;
		}
		p = p->succ;
		n--;
	}
	return max;
}
//归并排序
template<typename T>
void List<T>::mergesort(ListNode<T>* p, int start, int n) {
	cout << "start " << start << " n " << n << endl;
	if (start == n) {
		show_data();
		return;
	}
	int mid = (n+start) / 2;
	mergesort(p, start, mid);
	mergesort(p, mid + 1, n);
	ListNode<T>* m = p;
	ListNode<T>* q = p;
	int count_m = 0;
	int count_q = 0;
	while (count_m < start) {
		m = m->succ;
		count_m++;
	}
	while (count_q <= mid) {
		q = q->succ;
		count_q++;
	}
	ListNode<T>* head = m->pred;
	int i = start;
	int j = mid + 1;
	while (i <= mid && j <= n) {
		cout << "m.data: " << m->data << " q.data: " << q->data << endl;
		if (m->data <= q->data) {
			insertAsSucc(head, m->data);
			head = head->succ;
			i++;
			m = m->succ;
			remove(m->pred);
		}
		if(m->data>q->data) {
			insertAsSucc(head, q->data);
			head = head->succ;
			j++;
			q = q->succ;
			remove(q->pred);
		}
	}
	if (i > mid) {
		head->succ = q;
		show_data();
		return;
	}
	if (j > n) {
		head->succ = m;
		show_data();
		return;
	}
	//cout << "out start: " << start << " n " << n << endl;
}

/*=====================主函数=============================*/
int main() {
	/*ListNode<int> node_test(1); //创建节点
	cout << "当前节点node_test的地址: "<< &node_test << endl;
	node_test.insertAsPred(5); //插入前驱节点
	cout << "pred.data: " << node_test.pred->data<< "\npred.index: "<< node_test.pred<<"\npred.succ.index: " << node_test.pred->succ<<"\npred.pred: "<<node_test.pred->pred<<endl;
	*/
	List<int> list_test;
	list_test.insertAsFirst(4);
	cout << "header type: " << typeid(list_test.header).name() << typeid(list_test.header->succ).name() << endl;
	cout << "header->succ data: "<<list_test.header->succ->data << endl;
	cout << "first node data: "<<list_test.header->succ->data << endl;
	list_test.insertAsLast(2);
	cout << "trailer->pred data: "<<list_test.trailer->pred->data << endl;
	cout << "last node data: "<<list_test.trailer->pred->data << endl;
	cout << "after initialize the list size is: "<< list_test._size << endl;
	list_test.insertAsSucc(list_test.header->succ, 1);
	list_test.insertAsPred(list_test[2], 10);
	list_test.insertAsPred(list_test[2], 3);
	list_test.insertAsPred(list_test[2], 1);
	list_test.insertAsPred(list_test[2], 5);
	list_test.insertAsSucc(list_test[2], 6);
	list_test.insertAsSucc(list_test[2], 9);
	list_test.insertAsSucc(list_test[2], 8);
	cout << "after insert the size is: "<<list_test._size << endl;
	list_test.show_data();
	list_test.remove(list_test[2]);
	cout << "after remove node 2 : " << endl;
	list_test.show_data();
	//list_test.deduplicate();
	//cout << "after deduplicate :" << endl;
	//有序向量的查找
	//cout << list_test.search(1, list_test._size, list_test.trailer) << list_test.header->succ<<endl;
	list_test.uniquify();
	cout << "after uniquify :" << endl;
	list_test.show_data();
	//cout << "header:" << list_test.header << endl;
	//list_test.insertorder(list_test.header, list_test._size); //插入排序
	//list_test.selectorder(list_test.header, list_test._size); //选择排序
	list_test.mergesort(list_test.header,1,list_test._size);
	cout << "after inserorder :" << endl;
	list_test.show_data();
	cout<<"the max num is: "<<list_test.findmax(list_test.header->succ, list_test._size)->data<<endl;
	return 0;
}
