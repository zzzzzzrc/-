#include<iostream>
using namespace std;

template<typename T>
struct QueueNode {
	T data;
	QueueNode<T>* pred;
	QueueNode<T>* succ;
	QueueNode() {};
	QueueNode(T value, QueueNode<T>* p = NULL, QueueNode<T>* s = NULL) {
		data = value;
		pred = p;
		suss = s;
	}
};

template<typename T>
struct Queue{
public:
	int _size;
	QueueNode<T>* header;
	QueueNode<T>* trailer;
	Queue() {
		header = new QueueNode<T>;
		trailer = new QueueNode<T>;
		header->succ = trailer;
		trailer->pred = header;
		_size = 0;
	}
	QueueNode<T>* enqueue(T value); //进队列
	QueueNode<T>* dequeue(); //出队列
	void show_data();

};
//进队列
template<typename T>
QueueNode<T>* Queue<T>::enqueue(T value) {
	QueueNode<T>* newQueueNode = new QueueNode<T>;
	newQueueNode->data = value;
	newQueueNode->pred = trailer->pred;
	newQueueNode->succ = trailer;
	trailer->pred->succ = newQueueNode;
	trailer->pred = newQueueNode;
	_size++;
	return newQueueNode;
}
//出队列
template<typename T>
QueueNode<T>* Queue<T>::dequeue() {
	if (_size > 0) {
		QueueNode<T>* outNode = header->succ;
		header->succ = header->succ->succ;
		header->succ->succ->pred = header;
		_size--;
		return outNode;
	}
	else {
		return header;
	}
}
//打印队列数据
template<typename T>
void Queue<T>::show_data() {
	int count = 1;
	QueueNode<T>* p = header->succ;
	while (count <= _size) {
		cout << "the " << count-1 << " data is: " << p->data << endl;
		p = p->succ;
		count++;
	}
}

int main() {
	Queue<int> queue_test;
	queue_test.enqueue(1);
	queue_test.enqueue(2);
	queue_test.enqueue(3);
	queue_test.show_data();
	queue_test.dequeue();
	queue_test.show_data();
	return 0;
}