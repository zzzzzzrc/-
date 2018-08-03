#include<iostream>
#define DEFAULT_CAPACITY 3

using namespace std;
template<class T> 
class Vector
{
/*protected:
	int _size;
	int _capacity;
	T* _elem;*/
public:
	int _size;
	int _capacity;
	T* _elem;
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //���캯������ʼ��
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _size++)
		{
			_elem[_size] = v++;
		}
	}
	void show_element();
	void expand(); //����
	void shrink(); //����
	T& operator[](int r) const; //���������[]
	void permute(); //������������
	void permute1(Vector<T> &v);
	void unsort(int low, int high);//��������
	int find(T e, int low, int high) const;//Ѱ��Ԫ��e���������±�
	void insert(int index, T const & value); //��ȷ��λ�ò���Ԫ��
	int remove(int low, int high); //ɾ������[low,high)��Ԫ�أ�����ɾ��Ԫ�صĸ���
	int uniquify(); //Ψһ��
	int disordered() const; //�ж�������
	void pump_order(); //ð������
	int uniquify_order(); //��������Ψһ��  ������ ֱ���ж�ǰ��Ԫ���Ƿ����
	int uniquify_order_1(); //��������Ψһ��  �ظ�����ɾ��
	int uniquify_order_2(); //��������Ψһ�� ˫ָ�����һ�� 
	int search(T value, int low, int high); //���������Ĳ���
	int search_B(T value, int low, int high);
	void mergeSort(int low, int high); //�鲢����
};
// ��ӡ����Ԫ��
template<class T>
void Vector<T>::show_element() {
	for(int i=0;i<_size;i++)
		cout << _elem[i] << endl;
}

//ÿ��insert֮��Ӧ���д˺������鿴�Ƿ���Ҫ���ݣ���ֹoverflow
template<class T>
void Vector<T>::expand() {
	//���ݵ�����  size=capacity
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* old_elem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = old_elem[i];
	delete[] old_elem;
	cout << "expand" << endl;

}

template <class T>
void Vector<T>::shrink()
{
	//���ݵ����� sizeС���ķ�֮һ����
	if (_size << 2 > _capacity)
		return;
	//������һ�����С��Ĭ������
	if (_capacity >> 1 < DEFAULT_CAPACITY)
		return;
	// ����
	T* old_elem = _elem;
	_elem = new T[_capacity >>= 1 ];
	for (int i = 0; i < _size; i++)
		_elem[i] = old_elem[i];
	delete[] old_elem;
	cout << "shrink" << endl;
}


//����[] ������ֱ������   classname[i] = classname._elem[i]
template<class T>
T& Vector<T>::operator[](int r) const {
	return _elem[r];
}

//����û��������������
template<class T>
void Vector<T>::permute() {
	for (int i = _size; i > 0; i--)
	{
		swap(_elem[i-1], _elem[rand() % i]);//��ĩβ��ʼ����û���
	}
}

//������ʽ������
template<class T>
void Vector<T>::permute1(Vector<T> &v)
{
	for (int i = v._size; i > 0; i--)
		swap(v[i - 1], v[rand() % i]);
}

//��������
template<class T>
void Vector<T>::unsort(int low, int high) {
	T* v = _elem+low; //��low��ʼ����һ���µ�����
	for (int i = high - low; i > 0; i--)  //��ĩβ��ʼ��high��
		swap(v[i - 1], v[rand() % i]);
}

//���䣨���壩������������  ˳�����  ���ж������Ԫ��ʱȡ������ġ�
template<class T>
int Vector<T>::find(T e, int low, int high) const{
	if (low < 0 or high >= _size) {
		cout << "index error" << endl;
		return -1;
	}
	for (int i = high; i >= low; i--) {
		if (_elem[i] == e) {
			return i;
		}
	}
	cout << "not found in given range" << endl;
	return -1;
}

//�����ڲ���Ԫ��
template<class T>
void Vector<T>::insert(int index, T const &value) {
	expand(); //�ж��Ƿ���Ҫ����
	for (int i = _size; i > index; i--) {
		_elem[i] = _elem[i - 1];
	}
	_elem[index] = value;
	_size++; //����ʵ�ʹ�ģ+1
}

// ɾ��Ԫ��
template<class T>
int Vector<T>::remove(int low, int high) {
	if (low == high) {
		return 0;
	}
	int number = high - low;  //�Ƴ���Ԫ�ظ���
	for (int i = high; i < _size; i++) {    //[high,size-1] ��ǰ�ƶ�number��λ��
		//cout << low << ' ' << i << endl;
		_elem[low] = _elem[i];
		low++;
	}
	_size = low;
	return number;
}

//Ԫ��Ψһ��
template<class T>
int Vector<T>::uniquify() {
	int oldsize = _size;
	int i = 1;
	while (i<_size)
	{
		if (find(_elem[i], 0, i-1) != -1) //��elem[0:i-1]��Ѱ��elem[i]
		{
			remove(i, i + 1);	//�Ƴ�Ԫ��elem[i]
		}
		else
			i++;
	}
	return oldsize - _size;
}

//�ж�������
template<class T>
int Vector<T>::disordered() const{
	int count = 0;
	for (int i = 1; i < _size; i++) {
		if (_elem[i - 1] > _elem[i]) {
			count++;
		}
	}
	return count;
}

//ð������
template<class T>
void Vector<T>::pump_order() {
	for (int j = _size-1; j > 0; j--) {
		for (int i = 0; i < j; i++) {
			if (_elem[i] > _elem[i+1]) {
				swap(_elem[i], _elem[i+1]);
			}
		}
	}
}

//����������Ψһ��
template<class T>
int Vector<T>::uniquify_order() {
	int old_size = _size, i = 1;
	while (i < _size) {
		if (_elem[i - 1] == _elem[i]) {
			remove(i, i + 1);
		}
		else
			i++;
	}
	return old_size - _size;
}
//����������Ψһ�� �ظ�����ɾ��
template<class T>
int Vector<T>::uniquify_order_1() {
	int i = 0, j = 0, old_size = _size;
	while (j < _size) {
		if (_elem[i] != _elem[j]) {
			remove(i + 1, j);
			i++;
			j = i;
		}
		else
			j++;
	}
	return old_size - _size;
}
//��������Ψһ�� ˫ָ�����һ��
template<class T>
int Vector<T>::uniquify_order_2() {
	int i = 0, j = 0, old_size = _size;
	while (j < _size) {
		if (_elem[i] < _elem[j]) {
			i++;
			_elem[i] = _elem[j];
			j++;
		}
		else
			j++;
	}
	remove(i + 1, _size);
	return old_size - _size;
}
//����������Ԫ�ز���
template<class T>
int Vector<T>::search(T value, int low, int high) {
	T target = value;
	if (low > high) {
		return -1;
	}
	int mid = (low + high) / 2;
	if (_elem[mid] == target){
		return mid;
	}
	else if (_elem[mid] > target) {
		high = mid-1;
		return search(target, low, high);
	}
	else if (_elem[mid] < target) {
		low = mid + 1;
		return search(target, low, high);
	}
	return -1;
}
//��������Ԫ�ز���
template<class T>
int Vector<T>::search_B(T value, int low, int high) {
	int mid = (low + high) / 2;
	//cout << "index " << mid << endl;
	if (low+1 < high){		//���������䳤��Ϊ2   ��������ѭ��   _elem[9,10] mid = 9  _elem[mid]<= value  return search(9,10)
		if (_elem[mid] <= value) {
			return search_B(value, mid, high);
		}
		else {
			return search_B(value, low, mid - 1);
		}
	}
	else { //���䳤��Ϊ2�����
		if (_elem[low] == value) {
			for (int i = low; i < _size; i++) {		//�����ظ�Ԫ��  valueӦ�ò����λ��
				if (_elem[i] > value) {
					return i;
				}
			}
			return _size;	//���
		}
		if (_elem[high] == value) {
			for (int i = high; i < _size; i++) {		//�����ظ�Ԫ��  valueӦ�ò����λ��
				if (_elem[i] > value) {
					return i;
				}
			}
			return _size;
		}
		if (_elem[low] > value) {
			for (int i = low; i >= 0; i--) {
				if (_elem[i] < value){
					return (i + 1);
				}
			}
			return 0;
		}
		if (value < _elem[high] && value>_elem[low]) {
			return (low + 1);
		}
		if (_elem[high] < value) {
			for (int i = high; i < _size; i++) {
				if (_elem[i] > value){
					return i;
				}
			}
			return _size;
		}
	}
}
//�鲢����
template<class T>
void Vector<T>::mergeSort(int low, int high) {
	if (low >= high) {
		return;
	}
	int mid = (low + high) / 2;
	mergeSort(low, mid);

	mergeSort(mid + 1, high);
	
	int i = low, j = mid+1, k = 0;
	T* output = new T[high - low + 1];
	while (i <= mid && j <= high) {
		if (_elem[i] < _elem[j]) {
			output[k] = _elem[i];
			i++;
		}
		else {
			output[k] = _elem[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		while (j <= high) {
			output[k++] = _elem[j++];
		}
	}
	else {
		while (i <= mid) {
			output[k++] = _elem[i++];
		}
	}
	int l = 0;
	for (i = low; i <= high; i++) {
		_elem[i] = output[l];
		l++;
	}
	cout << "��������" << endl;
	for (i = low; i <= high; i++) {
		cout << _elem[i] << endl;
	}
}
 
int main()
{
	Vector <int> test(100,22,0);
	cout << test._capacity << endl;
	test.expand(); //����
	test.shrink(); //����
	cout << test._capacity << endl;
	//test.permute1(test);
	test.unsort(3, 16); //��������
	cout<< "after unsort num 3 is the " <<test.find(3,3,test._size-1) << " th number" << endl;
	//test.show_element();
	cout << test[22] << endl;
	for(int i = 0;i<10;i++)
		test.insert(1, 1);	//����[1]������100
	cout << "insert index 1 with num 1, the elem[1] is " << test[1] << " the last num is " << test[22] << endl;
	cout << "before unique the size is " << test._size << endl;
	//test.uniquify(); //Ψһ��
	cout << "after unique the size is " << test._size << endl;
	//test.remove(0, 5); //�Ƴ�[0:5] 01234��Ԫ��
	cout << "after remove elem[0:5] the size is " << test._size << endl;
	cout << "disordered num is " << test.disordered() << endl;
	/*-------------------------�����㷨------------------------------------*/
	cout << "����֮ǰ " << endl;
	test.show_element();
	//test.pump_order(); //ð������
	test.mergeSort(0, test._size - 1);//�鲢����
	//cout << "after ordered the disordered num is " << test.disordered() << endl;
	cout<< "����֮�� " << endl;
	test.show_element();
	/*-------------------------�������---------------------------------------*/
	//test.uniquify_order(); //��������Ψһ��
	//test.show_element();
	//test.uniquify_order_1(); // ��������Ψһ��
	test.uniquify_order_2(); // ��������Ψһ��
	cout << "search index " << test.search(100, 0, test._size - 1) << endl;
	//test.remove(13, 14);
	//test.show_element();
	cout << "search_B insert index " << test.search_B(100, 0, test._size - 1) << endl;
	return 0;
}