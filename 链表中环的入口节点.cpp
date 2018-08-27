#include<iostream>
using namespace std;

struct ListNode
{
	int value;
	ListNode* next;
	ListNode(int x) { value = x; next = NULL; }
};

ListNode* findEnterofCircle(ListNode* head)
{
	if (head == nullptr) {
		return nullptr;
	}
	ListNode* p = head;  //快指针
	ListNode* q = head;  // 慢指针
	int meet_flag = 0;
	int circle_count = 0;
	while (p->next && p->next->next)
	{
		if (p != q)
		{
			p = p->next->next;
			q = q->next;
			if (meet_flag == 2) {
				circle_count += 1;
			}
		}
		else {
			meet_flag += 1;
			p = p->next->next;
			q = q->next;
			if (meet_flag == 2) {   //第一次相遇
				circle_count += 1;
			}
			if (meet_flag == 3) {  //第二次相遇
				break;
			}
		}
	}
	if (circle_count == 0) {
		return nullptr;
	}
	else {
		p = head->next;
		q = head;
		int k = 1;  //p需要领先q的步数  为 circle的node个数
		while (p!=q) {
			if (k < circle_count)
			{
				p = p->next;
				k++;
			}
			else {
				p = p->next;
				q = q->next;
			}
		}
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
	//d->next = d;
	ListNode* node = findEnterofCircle(a);
	cout << node->value << endl;
	return 0;

}