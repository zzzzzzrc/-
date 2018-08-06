#include<iostream>
using namespace std;

#define DEFAULT_CAPACITY 5
template<typename T>
class Stack {
public:
	int _size;
	int _capacity;
	T* _elem;
	Stack(int capacity = DEFAULT_CAPACITY, int size = 0, T value = 0) {
		_elem = new T[_capacity = capacity]; //����ջ�ռ�
		for (int i = 0; i < size; i++) {
			_elem[i] = value;               //ջ�ڳ�ʼԪ�ظ�ֵ
		}
		_capacity = capacity;
		_size = size;
	}
	void show_data();
	void expand(); // ����
	T push(T const& value);//��ջ�ڶ���Ԫ��
	T pop();
	T top();
};
// ջ��Ԫ��
template<typename T>
T Stack<T>::top() {
	return _elem[_size - 1];
}
//��ӡջ��Ԫ��
template<typename T>
void Stack<T>::show_data() {
	for (int i = 0; i < _size; i++) {
		cout << "the num " << i << " data is " << _elem[i] << endl;
	}
}
//����
template<typename T>
void Stack<T>::expand() {
	if (_size == _capacity) {
		T* old_elem = _elem;
		_elem = new T[_capacity * 2];
		for (int i = 0; i < _size; i++) {
			_elem[i] = old_elem[i];
		}
		_capacity = _capacity * 2;
		delete[] old_elem;
	}
}
//��ջ�ڶ���Ԫ��
template<typename T>
T Stack<T>::push(T const& value) {
	expand();
	_elem[_size] = value;
	_size++;
	return value;
}
//ջ��Ԫ�س�ջ
template<typename T>
T Stack<T>::pop() {
	T* old_elem = _elem;
	_elem = new T[_capacity = _capacity];
	_size = _size - 1;
	for (int i = 0; i < _size; i++) {
		_elem[i] = old_elem[i];
	}
	T pop_data = old_elem[_size];
	delete[] old_elem;
	return pop_data;
}
void transfer(Stack<char>& s, int value, int k) {
	if (value == 0) {
		return;
	}
	static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	s.push(digit[value%k]);
	transfer(s, value / k, k);
	return;
}
//N�ʺ�����
struct Queen {
	int x;
	int y;
	Queen(int xx = 0, int yy = 0) {
		x = xx;
		y = yy;
	}
};
//�Ƚ������ʺ��Ƿ��ص�
bool compare_queen(Queen q, Queen p) {
	if (q.x == p.x || q.y == p.y || ((q.x + q.y) == (p.x + p.y)) || ((q.x - q.y) == (p.x - p.y))) {
		return true; //���ظ�
	}
	else {
		return false;//���ظ�
	}
}

void Nqueen(Queen q, Stack<Queen>& stack, int number) {
	while (stack._size < number && q.y <= number) {
		if (stack._size == 0) {  //ջ��  
			if (q.y < number) {  //���ʺ��ں���Χ�� ֱ����ջ
				cout << "in stack: " << "{" << q.x << "," << q.y << "}" << endl;
				stack.push(q);
				q.x++;
				q.y = 0;
			}
			else {  //ջ��ʱ  ��һ���ʺ��޷����� ���������̷�Χ��
				cout << "can not found path!" << endl;
				return;
			}
		}
		else {                   //ջ�ǿ�
			int count = stack._size - 1;
			while (count >= 0 && stack._size<number && q.y<number) {  //��ջ��Ԫ�رȽ�
				if (compare_queen(q, stack._elem[count])) { //���ظ� ��q.y++�����Ƚ�
					cout << "compare: " << "{" << q.x << "," << q.y << "}" << endl;
					q.y++;
					count = stack._size - 1;
				}
				else {  //û���ظ� �� ջ��Ԫ�رȽ����  ��ǰq��ջ  ��һ�м����Ƚ�
					if (count == 0) {
						cout << "compare: " << "{" << q.x << "," << q.y << "}" << endl;
						cout << "in stack: " << "{" << q.x << "," << q.y << "}" << endl;
						stack.push(q);
						q.x++;
						q.y = 0;
						count = stack._size - 1;
					}
					else {
						count--; //û���ظ����� ջ��Ԫ��û�бȽ����
					}
				}
			}
			//ջ��Ԫ�رȽ���� 
			if (stack._size < number && q.y == number) {  //ջδ��  �ҵ�ǰ�ʺ󳬳���Χ
				while (q.y == number && stack._size>0) {  //b��֤ջ����Ϊ��
					q = stack.pop();  //��һ���ʺ��ջ�������ǳ�����Χ��y����Ϊ�߽磩
				}
				q.y++;

			}
		}
	}
	cout << "done! stack_size:" << stack._size << endl;
	return;
}
/*======================������=================================
int main() {
	Stack<int> stack_test(5, 5, 2);
	stack_test.push(1);
	stack_test.show_data();
	cout << stack_test._capacity << endl;
	//����ת��
	Stack<char> stack_test_char;
	transfer(stack_test_char, 12345, 8);
	//stack_test_char.show_data();
	while (stack_test_char._size > 0) {
		cout << stack_test_char.pop() << endl;
	}
	Stack<Queen> qstack(5, 0, 0);
	Nqueen(Queen(0, 0), qstack, 6);
	for (int i = 0; i < qstack._size; i++) {
		cout << "{" << qstack._elem[i].x << "," << qstack._elem[i].y << "}" << endl;
	}
	return 0;
}
*/