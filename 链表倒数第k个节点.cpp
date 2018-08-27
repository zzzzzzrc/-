#include<iostream>
using namespace std;

struct ListNode
{
	int value;
	ListNode* next;
	ListNode(int x) { value = x; next = NULL; }
};


//双指针  先拉开k的距离 再同步运动  这样当第一个指针到终点时，第二个刚好距离终点k
ListNode* findKtotail(int k,ListNode* head)
{
	if (k <= 0 || head == nullptr)
	{
		return nullptr;
	}
	ListNode* p = head;
	ListNode* q = head;
	int count = 0;
	while (p)
	{
		if (count < k)
		{
			p = p->next;
			count++;
		}
		else {
			p = p->next;
			q = q->next;
			count++;
		}
	}
	if (count < k) {
		return nullptr;
	}
	else {
		return q;
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
	ListNode* node = findKtotail(1, a);
	cout << node->value << endl;
	return 0;
}