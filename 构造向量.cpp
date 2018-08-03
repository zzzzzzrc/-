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
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //构造函数，初始化
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _size++)
		{
			_elem[_size] = v++;
		}
	}
	void show_element();
	void expand(); //扩容
	void shrink(); //缩容
	T& operator[](int r) const; //重载运算符[]
	void permute(); //向量整体置乱
	void permute1(Vector<T> &v);
	void unsort(int low, int high);//区间置乱
	int find(T e, int low, int high) const;//寻找元素e并返回其下标
	void insert(int index, T const & value); //在确定位置插入元素
	int remove(int low, int high); //删除区间[low,high)的元素，返回删除元素的个数
	int uniquify(); //唯一化
	int disordered() const; //判断有序性
	void pump_order(); //冒泡排序
	int uniquify_order(); //有序向量唯一化  暴力法 直接判断前后元素是否相等
	int uniquify_order_1(); //有序向量唯一化  重复区间删除
	int uniquify_order_2(); //有序向量唯一化 双指针遍历一遍 
	int search(T value, int low, int high); //有序向量的查找
	int search_B(T value, int low, int high);
	void mergeSort(int low, int high); //归并排序
};
// 打印向量元素
template<class T>
void Vector<T>::show_element() {
	for(int i=0;i<_size;i++)
		cout << _elem[i] << endl;
}

//每次insert之间应运行此函数，查看是否需要扩容，防止overflow
template<class T>
void Vector<T>::expand() {
	//扩容的条件  size=capacity
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
	//缩容的条件 size小于四分之一容量
	if (_size << 2 > _capacity)
		return;
	//容量缩一半后不能小于默认容量
	if (_capacity >> 1 < DEFAULT_CAPACITY)
		return;
	// 缩容
	T* old_elem = _elem;
	_elem = new T[_capacity >>= 1 ];
	for (int i = 0; i < _size; i++)
		_elem[i] = old_elem[i];
	delete[] old_elem;
	cout << "shrink" << endl;
}


//重载[] 向量类直接引用   classname[i] = classname._elem[i]
template<class T>
T& Vector<T>::operator[](int r) const {
	return _elem[r];
}

//随机置换，构造随机向量
template<class T>
void Vector<T>::permute() {
	for (int i = _size; i > 0; i--)
	{
		swap(_elem[i-1], _elem[rand() % i]);//从末尾开始随机置换。
	}
}

//重载形式的置乱
template<class T>
void Vector<T>::permute1(Vector<T> &v)
{
	for (int i = v._size; i > 0; i--)
		swap(v[i - 1], v[rand() % i]);
}

//区间置乱
template<class T>
void Vector<T>::unsort(int low, int high) {
	T* v = _elem+low; //从low开始构造一个新的向量
	for (int i = high - low; i > 0; i--)  //从末尾开始（high）
		swap(v[i - 1], v[rand() % i]);
}

//区间（整体）无序向量查找  顺序查找  当有多个命中元素时取索引大的。
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

//向量内插入元素
template<class T>
void Vector<T>::insert(int index, T const &value) {
	expand(); //判断是否需要扩容
	for (int i = _size; i > index; i--) {
		_elem[i] = _elem[i - 1];
	}
	_elem[index] = value;
	_size++; //向量实际规模+1
}

// 删除元素
template<class T>
int Vector<T>::remove(int low, int high) {
	if (low == high) {
		return 0;
	}
	int number = high - low;  //移除的元素个数
	for (int i = high; i < _size; i++) {    //[high,size-1] 向前移动number个位置
		//cout << low << ' ' << i << endl;
		_elem[low] = _elem[i];
		low++;
	}
	_size = low;
	return number;
}

//元素唯一化
template<class T>
int Vector<T>::uniquify() {
	int oldsize = _size;
	int i = 1;
	while (i<_size)
	{
		if (find(_elem[i], 0, i-1) != -1) //在elem[0:i-1]中寻找elem[i]
		{
			remove(i, i + 1);	//移除元素elem[i]
		}
		else
			i++;
	}
	return oldsize - _size;
}

//判断有序性
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

//冒泡排序
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

//有序向量的唯一化
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
//有序向量的唯一化 重复区间删除
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
//有序向量唯一化 双指针遍历一遍
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
//有序向量的元素查找
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
//有序向量元素查找
template<class T>
int Vector<T>::search_B(T value, int low, int high) {
	int mid = (low + high) / 2;
	//cout << "index " << mid << endl;
	if (low+1 < high){		//最后查找区间长度为2   可能陷入循环   _elem[9,10] mid = 9  _elem[mid]<= value  return search(9,10)
		if (_elem[mid] <= value) {
			return search_B(value, mid, high);
		}
		else {
			return search_B(value, low, mid - 1);
		}
	}
	else { //区间长度为2的情况
		if (_elem[low] == value) {
			for (int i = low; i < _size; i++) {		//考虑重复元素  value应该插入的位置
				if (_elem[i] > value) {
					return i;
				}
			}
			return _size;	//最后
		}
		if (_elem[high] == value) {
			for (int i = high; i < _size; i++) {		//考虑重复元素  value应该插入的位置
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
//归并排序
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
	cout << "区间排序" << endl;
	for (i = low; i <= high; i++) {
		cout << _elem[i] << endl;
	}
}
 
int main()
{
	Vector <int> test(100,22,0);
	cout << test._capacity << endl;
	test.expand(); //扩容
	test.shrink(); //缩容
	cout << test._capacity << endl;
	//test.permute1(test);
	test.unsort(3, 16); //区间置乱
	cout<< "after unsort num 3 is the " <<test.find(3,3,test._size-1) << " th number" << endl;
	//test.show_element();
	cout << test[22] << endl;
	for(int i = 0;i<10;i++)
		test.insert(1, 1);	//向量[1]处插入100
	cout << "insert index 1 with num 1, the elem[1] is " << test[1] << " the last num is " << test[22] << endl;
	cout << "before unique the size is " << test._size << endl;
	//test.uniquify(); //唯一化
	cout << "after unique the size is " << test._size << endl;
	//test.remove(0, 5); //移除[0:5] 01234的元素
	cout << "after remove elem[0:5] the size is " << test._size << endl;
	cout << "disordered num is " << test.disordered() << endl;
	/*-------------------------排序算法------------------------------------*/
	cout << "排序之前 " << endl;
	test.show_element();
	//test.pump_order(); //冒泡排序
	test.mergeSort(0, test._size - 1);//归并排序
	//cout << "after ordered the disordered num is " << test.disordered() << endl;
	cout<< "排序之后 " << endl;
	test.show_element();
	/*-------------------------排序结束---------------------------------------*/
	//test.uniquify_order(); //有序向量唯一化
	//test.show_element();
	//test.uniquify_order_1(); // 有序向量唯一化
	test.uniquify_order_2(); // 有序向量唯一化
	cout << "search index " << test.search(100, 0, test._size - 1) << endl;
	//test.remove(13, 14);
	//test.show_element();
	cout << "search_B insert index " << test.search_B(100, 0, test._size - 1) << endl;
	return 0;
}