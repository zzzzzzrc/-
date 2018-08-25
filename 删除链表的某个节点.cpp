#include<iostream>
using namespace std;

struct ListNode {
	int value;
	ListNode* next;
};

void deletenode(ListNode** head, ListNode* tobeDeleted) {
	if (head == nullptr || *head == nullptr) {
		return;
	}
	if (tobeDeleted == *head) {  //���ɾ�������׽ڵ�
		ListNode* node = tobeDeleted;
		*head = tobeDeleted->next;
		delete node;
		node = nullptr;
		return;
	}
	if (tobeDeleted->next == nullptr) { //���ɾ������β�ڵ�
		ListNode* node = *head;
		while (node->next != tobeDeleted) {
			node = node->next;
		}
		node->next = nullptr;
		delete tobeDeleted;
		tobeDeleted = nullptr;
		return;
	}
	ListNode* node = tobeDeleted->next;
	tobeDeleted->value = node->value;
	tobeDeleted->next = node->next;
	delete node;
	node = nullptr;
	return;
}

int main() {
	ListNode* a = new ListNode();
	a->value = 1;
	ListNode* b = new ListNode();
	b->value = 2;
	ListNode* c = new ListNode();
	c->value = 3;
	a->next = b;
	b->next = c;
	c->next = nullptr;
	ListNode** head = new ListNode*();
	head = &a;

	deletenode(head, c);
	
	cout << "aָ��ĵ�ַ��struct�ĵ�ַ��:" << a << '\t'<<"&a��a����ĵ�ַ��:" << &a << endl;
	cout << "headָ��ĵ�ַ��ָ��a�ĵ�ַ��:" << head << '\t' << "*head��ָ��a,Ҳ����struct�ĵ�ַ��" << *head<<endl;
	return 0;
	
}