#include<iostream>

using namespace std;
//函数模板
/*template <class T>
T getmax(T a, T b)
{
	return(a > b ? a : b);
}

int main()
{
	int a1 = 10, b1 = 9;
	float a2 = 4.311, b2 = 5.623;
	cout << getmax<int>(a1, b1) << endl;
	cout << getmax<float>(a2, b2) << endl;

	return 0;
}*/

//类模板
template <class T>
class myclass
{
	T value1, value2;
public:
	myclass(T first, T second)
	{
		value1 = first;
		value2 = second;
	}
	T getmax(T c,T d);
};
//类外定义成员函数
template <class T>
T myclass<T>::getmax(T c,T d)
{
	return (c+d)/(value1+value2);
}


//调用
int main()
{
	myclass<int> myclass1(10, 9);
	myclass<double> myclass2(5.3, 6.1);
	cout << myclass1.value1 << endl;
	cout << myclass1.getmax(10,9) << endl;
	cout << myclass2.getmax(5.3,6.1) << endl;
	return 0;
}