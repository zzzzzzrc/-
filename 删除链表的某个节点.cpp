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
	if (tobeDeleted == *head) {  //如果删除的是首节点
		ListNode* node = tobeDeleted;
		*head = tobeDeleted->next;
		delete node;
		node = nullptr;
		return;
	}
	if (tobeDeleted->next == nullptr) { //如果删除的是尾节点
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
	
	cout << "a指向的地址（struct的地址）:" << a << '\t'<<"&a（a本身的地址）:" << &a << endl;
	cout << "head指向的地址（指针a的地址）:" << head << '\t' << "*head（指针a,也就是struct的地址）" << *head<<endl;
	return 0;
	
}