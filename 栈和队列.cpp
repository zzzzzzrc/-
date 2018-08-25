#include<iostream>
#include<stack>
#include<queue>
using namespace std;

//��ջ ʵ�ֶ���
template<typename T>
class CQueue
{
public:
	CQueue() {};//���캯��
	~CQueue() {}; //��������
	void appendTail(const T value);
	T deleteHead();
private:
	stack<T> stack1;
	stack<T> stack2;
};

template<typename T>
void CQueue<T>::appendTail(const T value) {
	stack1.push(value);
}

template<typename T>
T CQueue<T>::deleteHead() {
	if (stack2.size() <= 0) {
		while (stack1.size() > 0) {   //��ջ2Ϊ��ʱ����ջ1Ԫ����һѹ��ջ2
			T node = stack1.top();
			stack1.pop();
			stack2.push(node);
		}
	}
	if (stack2.size() == 0) {    //ջ2��Ϊ��  �׳��쳣
		throw new exception("queue is empty");
	}
	T deletenode = stack2.top();   //ջ2��Ԫ�س�ջ  �����׳���
	stack2.pop();
	return deletenode;
}


//�ö���ʵ��ջ
template<typename T>
class CStack
{
public:
	CStack() {};
	~CStack() {};
	void CStack_push(const T value);
	T CStack_pop();
private:
	queue<T> queue1;
	queue<T> queue2;
};

template<typename T>
void CStack<T>::CStack_push(const T value) {
	queue1.push(value);
}
template<typename T>
T CStack<T>::CStack_pop() {
	while (queue1.size() > 1) {
		T node = queue1.front();
		queue1.pop();
		queue2.push(node);
	}
	T pop_node = queue1.front();
	queue1.pop();
	while (queue2.size() > 0) {
		T node1 = queue2.front();
		queue2.pop();
		queue1.push(node1);
	}
	return pop_node;
}


int main() {
	/*CQueue<int> test;
	test.appendTail(1);
	test.appendTail(2);
	test.deleteHead();
	//test.deleteHead();
	int head = test.deleteHead();
	cout << head << endl;*/
	CStack<int> test1;
	test1.CStack_push(1);
	test1.CStack_push(2);
	test1.CStack_push(3);
	test1.CStack_pop();
	//test1.CStack_push(4);
	int pop = test1.CStack_pop();
	cout << pop << endl;

}

