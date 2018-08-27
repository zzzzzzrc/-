#include<iostream>
using namespace std;

struct ListNode
{
	int value;
	ListNode* next;
	ListNode(int x) { value = x; next = NULL; }
};

ListNode* reverse(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
	{
		return head;
	}
	else {
		ListNode* pred;
		pred = new ListNode(0);
		ListNode* succ;
		succ = new ListNode(0);
		ListNode* p = head;
		succ->next = p->next;
		while (p->next) {
			if (pred->next == NULL) {
				p->next = nullptr;
			}
			else
			{
				p->next = pred->next;
			}
			pred->next = p;
			p = succ->next;
			if (p->next)
			{
				succ->next = p->next;
			}
		}
		p->next = pred->next;
		delete pred;
		delete succ;
		return p;
	}
}

int main()
{
	ListNode* a = NULL;
	a = new ListNode(1);
	ListNode* b = NULL;
	b = new ListNode(2);
	ListNode* c = NULL;
	c = new ListNode(3);
	ListNode* d = NULL;
	d = new ListNode(4);
	a->next = b;
	b->next = c;
	c->next = d;
	ListNode* head = reverse(a);
	while (head) {
		cout << head->value << endl;
		head = head->next;
	}
	return 0;
}