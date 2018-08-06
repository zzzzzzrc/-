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
		_elem = new T[_capacity = capacity]; //开辟栈空间
		for (int i = 0; i < size; i++) {
			_elem[i] = value;               //栈内初始元素赋值
		}
		_capacity = capacity;
		_size = size;
	}
	void show_data();
	void expand(); // 扩容
	T push(T const& value);//向栈内堆入元素
	T pop();
	T top();
};
// 栈顶元素
template<typename T>
T Stack<T>::top() {
	return _elem[_size - 1];
}
//打印栈内元素
template<typename T>
void Stack<T>::show_data() {
	for (int i = 0; i < _size; i++) {
		cout << "the num " << i << " data is " << _elem[i] << endl;
	}
}
//扩容
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
//向栈内堆入元素
template<typename T>
T Stack<T>::push(T const& value) {
	expand();
	_elem[_size] = value;
	_size++;
	return value;
}
//栈顶元素出栈
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
//N皇后问题
struct Queen {
	int x;
	int y;
	Queen(int xx = 0, int yy = 0) {
		x = xx;
		y = yy;
	}
};
//比较两个皇后是否重叠
bool compare_queen(Queen q, Queen p) {
	if (q.x == p.x || q.y == p.y || ((q.x + q.y) == (p.x + p.y)) || ((q.x - q.y) == (p.x - p.y))) {
		return true; //有重复
	}
	else {
		return false;//无重复
	}
}

void Nqueen(Queen q, Stack<Queen>& stack, int number) {
	while (stack._size < number && q.y <= number) {
		if (stack._size == 0) {  //栈空  
			if (q.y < number) {  //若皇后在合理范围内 直接入栈
				cout << "in stack: " << "{" << q.x << "," << q.y << "}" << endl;
				stack.push(q);
				q.x++;
				q.y = 0;
			}
			else {  //栈空时  第一个皇后无法放置 （超出棋盘范围）
				cout << "can not found path!" << endl;
				return;
			}
		}
		else {                   //栈非空
			int count = stack._size - 1;
			while (count >= 0 && stack._size<number && q.y<number) {  //与栈内元素比较
				if (compare_queen(q, stack._elem[count])) { //有重复 则q.y++继续比较
					cout << "compare: " << "{" << q.x << "," << q.y << "}" << endl;
					q.y++;
					count = stack._size - 1;
				}
				else {  //没有重复 且 栈内元素比较完成  当前q入栈  下一行继续比较
					if (count == 0) {
						cout << "compare: " << "{" << q.x << "," << q.y << "}" << endl;
						cout << "in stack: " << "{" << q.x << "," << q.y << "}" << endl;
						stack.push(q);
						q.x++;
						q.y = 0;
						count = stack._size - 1;
					}
					else {
						count--; //没有重复但是 栈内元素没有比较完成
					}
				}
			}
			//栈内元素比较完成 
			if (stack._size < number && q.y == number) {  //栈未满  且当前皇后超出范围
				while (q.y == number && stack._size>0) {  //b保证栈不能为空
					q = stack.pop();  //上一个皇后出栈，若还是超出范围（y不能为边界）
				}
				q.y++;

			}
		}
	}
	cout << "done! stack_size:" << stack._size << endl;
	return;
}
/*======================主函数=================================
int main() {
	Stack<int> stack_test(5, 5, 2);
	stack_test.push(1);
	stack_test.show_data();
	cout << stack_test._capacity << endl;
	//进制转换
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