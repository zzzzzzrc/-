#include <iostream>
#include <typeinfo>
using namespace std;


/*-----------------------------�б�ڵ���--------------------------------*/
template<typename T> 
struct ListNode {
	//���ݳ�Ա
	T data;
	ListNode<T>* pred; //ָ��ListNode���͵�ָ��
	ListNode<T>* succ;
	ListNode() {};   //�������캯��
	//���캯��
	ListNode(T value, ListNode<T>* p = NULL, ListNode<T>* s = NULL) {
		data = value;
		pred = p;
		succ = s;
	}
	//��Ա����
	ListNode<T>*  insertAsPred(T const& e); //���뵱ǰ�ڵ��ǰ����㣬��������λ��
	ListNode<T>*  insertAsSucc(T const& e); // ��̽ڵ�
};

template<typename T>
ListNode<T>*  ListNode<T>::insertAsPred(T const& e) {
	//ListNode<T> tmp(e); //����ǰ���ڵ�
	//tmp.succ = this;    //cur����ǰ���ڵ�ĺ�̽ڵ�Ϊcur
	//pred = &tmp;        //cur����ǰ���ڵ�Ϊtmp
	ListNode<T>* tmp = new ListNode<T>;
	tmp->data = e;
	tmp->pred = pred;
	tmp->succ = this;
	if (pred != NULL) {
		pred->succ = tmp; //��ǰ����ǰ����� �ĺ�̽��Ϊx��ԭ��Ϊ��ǰ��㣩 ��ʱδ�ı�pred
	}
	pred = tmp; //��ǰ����ǰ�����Ϊ tmp
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

/*---------------------�б���-----------------------------*/
template<class T>
class List {
private:
	//int _size;
	//ListNode<T>* header;
	//ListNode<T>* trailer; //ͷβ�ڱ��ڵ�
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
	List(List<T> const & L); //���������б�L
	List(List<T> const & L, int r, int n); //�����б�L�ӵ�r��node��ʼ��n��
	ListNode<T>* operator [](int r); //���������[] ���ȷ���
	ListNode<T>* header;
	ListNode<T>* trailer; //ͷβ�ڱ��ڵ�
	//ListNode<T>* first;  //�׽ڵ�
	//ListNode<T>* last;   //ĩ�ڵ�
	ListNode<T>* find(T const& value, int n, ListNode<T>* p) const;  //�ӽڵ�p��ʼ��n���ڵ�����ֵΪvalue�Ľڵ�
	ListNode<T>* insertAsFirst(T const& value); //��Ϊ�׽ڵ�����б� dataΪvalue 
	ListNode<T>* insertAsLast(T const& value); //��Ϊ�׽ڵ�����б� dataΪvalue
	ListNode<T>* insertAsPred(ListNode<T>* p, T const& value); //��Ϊp��ǰ��������
	ListNode<T>* insertAsSucc(ListNode<T>* p, T const& value); //��Ϊp�ĺ�̽�����
	void copynode(ListNode<T>* p, int n); //���ڸ��ƵĹ���
	void show_data();
	T remove(ListNode<T>* p);
	~List();//��������
	int clear();//����б������н��
	int deduplicate();//�����б�ȥ��
	int uniquify(); //�����б�ȥ��
	ListNode<T>* search(T value, int n, ListNode<T>* p); //�����б�Ĳ���
	void insertorder(ListNode<T>* p, int n);//�������� p�ڵ�ǰ��n����������
	void selectorder(ListNode<T>* p, int n);//ѡ������ p�ڵ���n����������
	ListNode<T>* findmax(ListNode<T>* p, int n);//�ڽڵ�p���棨����p��n���ڵ����ҵ����� �����ظ��� ѡ�񿿺��
	void mergesort(ListNode<T>* p, int start, int n); //�鲢����
	//void merge(int start, int end);
};
//���캯��   ��ʼ��List
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
//��������� [] �ܹ���rank����Ԫ�ص�ֵ
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
//�ڵ�p֮ǰn���ڵ��в���ֵΪvalue�Ľڵ�
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
//��Ϊ�׽ڵ�����б�
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
//��Ϊβ�ڵ�����б�
template<typename T>
ListNode<T>* List<T>::insertAsLast(T const& value) {
	trailer->insertAsPred(value);
	_size++;
	return trailer->pred;
}
//��Ϊ�ڵ�p��ǰ�����
template<typename T>
ListNode<T>* List<T>::insertAsPred(ListNode<T>* p, T const& value) {
	_size++;
	return p->insertAsPred(value);
}
//��Ϊ�ڵ�p�ĺ�̽ڵ�
template<typename T>
ListNode<T>* List<T>::insertAsSucc(ListNode<T>* p, T const& value) {
	_size++;
	return p->insertAsSucc(value);
}
//���ڸ��ƵĹ���
template<typename T>
void List<T>::copynode(ListNode<T>* p, int n) {
	init();
	while (n > 0) {
		insertAsLast(p->data);
		p = p->succ;
		n--;
	}
}
//���ڸ��ƵĹ��췽��  ��p��ʼ��n��
template<typename T>
List<T>::List(ListNode<T>* p, int n) {
	copynode(p, n);
}
template<typename T> //��������L
List<T>::List(List<T> const & L) {
	copynode(L.header.succ, L._size);
}
template<typename T> //�����б�L�ĵ�r����ʼ ��n��
List<T>::List(List<T> const & L, int r, int n) {
	copynode(L[r], n);
}
//��ӡ���н���data
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
//ɾ��ĳ�ڵ�
template<typename T>
T List<T>::remove(ListNode<T>* p) {
	T tmp_data = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return tmp_data;
}
//��������
template<typename T>
List<T>::~List() {
	clear(); // ����б������е�node
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
//�����б��ȥ��
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
//�����б��ȥ��
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
//�����б�Ĳ���
template<typename T>
ListNode<T>* List<T>::search(T value, int n, ListNode<T>* p) {
	ListNode<T>* m = NULL;
	while (n > 0 && p->pred) {
		if (p->pred->data > value) {
			p = p->pred;
			n--;
		}
		else {
			return p->pred;  //���ز�����value�Ľڵ㣬��Ҫ����ڵ㣬��return�Ľڵ�->succΪ����Ľڵ�
		}
	}
	cout << "not found!" << endl;
	return  m; // �׳��쳣���ʵ�֣�������߽�
}

//��������
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
//ѡ������
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
//�鲢����
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

/*=====================������=============================*/
int main() {
	/*ListNode<int> node_test(1); //�����ڵ�
	cout << "��ǰ�ڵ�node_test�ĵ�ַ: "<< &node_test << endl;
	node_test.insertAsPred(5); //����ǰ���ڵ�
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
	//���������Ĳ���
	//cout << list_test.search(1, list_test._size, list_test.trailer) << list_test.header->succ<<endl;
	list_test.uniquify();
	cout << "after uniquify :" << endl;
	list_test.show_data();
	//cout << "header:" << list_test.header << endl;
	//list_test.insertorder(list_test.header, list_test._size); //��������
	//list_test.selectorder(list_test.header, list_test._size); //ѡ������
	list_test.mergesort(list_test.header,1,list_test._size);
	cout << "after inserorder :" << endl;
	list_test.show_data();
	cout<<"the max num is: "<<list_test.findmax(list_test.header->succ, list_test._size)->data<<endl;
	return 0;
}
