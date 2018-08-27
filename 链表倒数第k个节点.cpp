#include<iostream>
using namespace std;

struct ListNode
{
	int value;
	ListNode* next;
	ListNode(int x) { value = x; next = NULL; }
};


//˫ָ��  ������k�ľ��� ��ͬ���˶�  ��������һ��ָ�뵽�յ�ʱ���ڶ����պþ����յ�k
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