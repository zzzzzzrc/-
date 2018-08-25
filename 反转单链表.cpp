#include<iostream>
using namespace std;
struct ListNode {
	int value;
	ListNode* next;
};

void tranverse(ListNode* node) {
	ListNode* p = nullptr;
	ListNode* q = nullptr;
	while (node) {    //��ת������ĺ��Ĳ���
		ListNode* p = node->next; //��¼��ǰ�ڵ����һ���ڵ�
		node->next = q;			//��ǰ�ڵ����һ���ڵ�Ϊq ֮ǰ�����Ľڵ㣨��ת��
		q = node;              //qָ��ǰ�ڵ�  �Ա���һ���ڵ�ָ����
		node = p;              //������һ���ڵ�
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