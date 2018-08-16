#include<iostream>
#include<stack>
using namespace std;
struct ListNode
{
	int value;
	ListNode* next;
};

void AddToTail(ListNode** head, int value) {
	ListNode* new_node = new ListNode();
	new_node->value = value;
	new_node->next = nullptr;
	if (*head == nullptr) {
		*head = new_node;
	}
	else {
		ListNode* preNode = *head;
		while (preNode->next != nullptr) {
			preNode = preNode->next;
		}
		preNode->next = new_node;
	}
}

void DeleteNode(ListNode** head, int value) // 删除第一个值为value的节点
{
	if (head == nullptr || *head == nullptr) { //head指向空指针 或者head指向的指针为空指针（一般情况下head指向的指针为头节点）
		return;
	}
	ListNode* NodeToBeDelete = nullptr;
	if ((*head)->value == value) {	//头节点即为删除的节点
		NodeToBeDelete = *head;
		*head = (*head)->next;
	}
	else {
		ListNode* node = *head;
		while (node->next != nullptr && node->next->value != value) {  //寻找删除的节点
			node = node->next;
		}
		if (node->next != nullptr && node->next->value == value) {  //如果找到的话
			NodeToBeDelete = node->next;
			node->next = node->next->next;
		}
	}
	delete NodeToBeDelete;
	NodeToBeDelete = nullptr;
}

void printnode(ListNode* node) {
	if (node == nullptr) {
		return;
	}
	else {
		printnode(node->next);
		cout << node->value << endl;
	}
}
void PrintNodeValue(ListNode** head,int mode) {  //0用栈来实现倒序输出  1递归
	if (mode == 0) {
		stack<int> value_stack;
		if (head == nullptr || *head == nullptr) {
			return;
		}
		else {
			ListNode* node = *head;
			while (node != nullptr) {
				value_stack.push(node->value);
				node = node->next;
			}
			while (!value_stack.empty()) {
				int value = value_stack.top();
				cout << value << endl;
				value_stack.pop();
			}
		}
	}
	else { //递归实现
		ListNode* node = *head;
		printnode(node);
	}
}

int main() {
	ListNode* node = new ListNode();
	node->value = 0;
	node->next = nullptr;
	cout << "node addr:" << node << endl;
	ListNode* node1 = nullptr;
	ListNode** phead = &node;
	cout << "phead addr:" << phead << endl;
	AddToTail(phead, 1);
	AddToTail(phead, 2);
	AddToTail(phead, 3);
	cout << (*phead)->next->value<< endl;
	//DeleteNode(phead, 2);
	cout << (*phead)->next->value << endl;
	cout << "倒序输出" << endl;
	PrintNodeValue(phead,1);
	return 0;
}