#include<iostream>
using namespace std;

struct ListNode
{
	int value;
	ListNode* next;
	ListNode(int x) { value = x; next = NULL; }
};

ListNode* merge(ListNode* phead, ListNode* qhead)
{
	if (phead == NULL && qhead != NULL) {
		return qhead;
	}
	if (phead != NULL && qhead == NULL) {
		return qhead;
	}
	if (phead == NULL && qhead == NULL) {
		return nullptr;
	}
	ListNode* p = phead;
	ListNode* q = qhead;
	ListNode* cur_node;
	cur_node = new ListNode(0);
	ListNode* head = cur_node;
	while (p&&q)
	{
		if (p->value <= q->value) {
			cur_node->next = p;
			cur_node = p;
			p = p->next;
		}
		else {
			cur_node->next = q;
			cur_node = q;
			q = q->next;
		}
	}
	if (!p) {
		cur_node->next = q;
	}
	else
	{
		cur_node->next = p;
	}
	return head->next;
}

int main()
{
	ListNode* a;
	a = new ListNode(1);
	ListNode* b;
	b = new ListNode(3);
	ListNode* c;
	c = new ListNode(4);
	ListNode* d;
	d = new ListNode(6);
	a->next = b;
	b->next = c;
	c->next = d;
	ListNode* a1;
	a1 = new ListNode(2);
	ListNode* b1;
	b1 = new ListNode(5);
	ListNode* c1;
	c1 = new ListNode(5);
	ListNode* d1;
	d1 = new ListNode(8);
	a1->next = b1;
	b1->next = c1;
	c1->next = d1;
	ListNode* head = merge(a, a1);
	while (head)
	{
		cout << head->value;
		head = head->next;
	}
	return 0;
}