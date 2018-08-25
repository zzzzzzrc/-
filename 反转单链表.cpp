#include<iostream>
using namespace std;
struct ListNode {
	int value;
	ListNode* next;
};

void tranverse(ListNode* node) {
	ListNode* p = nullptr;
	ListNode* q = nullptr;
	while (node) {    //反转单链表的核心操作
		ListNode* p = node->next; //记录当前节点的下一个节点
		node->next = q;			//当前节点的下一个节点为q 之前遍历的节点（反转）
		q = node;              //q指向当前节点  以便下一个节点指向它
		node = p;              //遍历下一个节点
	}
}

int main() {
	ListNode* head = new ListNode();
	ListNode* node1 = new ListNode();
	ListNode* node2 = new ListNode();
	ListNode* node3 = new ListNode();
	head->value = 1;
	head->next = node1;
	node1->value = 2;
	node1->next = node2;
	node2->value = 3;
	node2->next = node3;
	node3->value = 4;
	node3->next = nullptr;
	tranverse(head);
	ListNode* node = node3;
	while (node)
	{
		cout << node->value << endl;
		node = node->next;
	}
}