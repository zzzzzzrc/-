#include<iostream>
using namespace std;
//时间复杂度为O(n) 空间复杂度O(n)
int fun1(int* test_array, int length) {
	//int length = sizeof(test_array) / sizeof(test_array[0]);   //传入的是一个指针  sizeof为4 
	int* array = new int[length];
	for (int i = 0; i < length; i++)
	{
		array[i] = 0;
	}
	for (int j = 0; j < length; j++)
	{
		if (test_array[j]<0 || test_array[j]>(length - 1))
		{
			return false;
		}
		array[test_array[j]] += 1;
		if (array[test_array[j]] > 1)
		{
			return test_array[j];
		}
	}
	return 0;
}


//时间复杂度O(n) 空间复杂度O(1)
int fun2(int* test_array, int length)
{
	int i = 0;
	while (i < length)
	{
		if (test_array[i]<0 || test_array[i]>(length - 1))
		{
			return false;
		}
		if (test_array[i] == i)
		{
			i++;
		}
		else {
			if (test_array[i] == test_array[test_array[i]]) {
				return test_array[i];
			}
			else {
				int temp = test_array[test_array[i]];
				test_array[test_array[i]] = test_array[i];
				test_array[i] = temp;
			}
		}
	}
	return 0;
}

// n+1 长的数组， 取值范围 1~n  至少有一个重复的数  找出一个重复的数
int fun3(int* test_array, int length)
{
	int start = 1;
	int end = length - 1;
	int middle = (end - start) / 2 + start;
	while (start <= middle)
	{
		int count = 0;
		for (int i = 0; i < length; i++)
		{
			if (test_array[i] >= start && test_array[i] <= middle)
			{
				count += 1;
			}
		}
		if (start == middle)
		{
			if (count <= 1) {
				return end;
			}
			else {
				return start;
			}
		}

		if (count <= middle-start+1)
		{
			start = middle + 1;
			//end = end;
			middle = (end - start) / 2 + start;
		}
		else{
			//start = start;
			end = middle;
			middle = (end - start) / 2 + start;
		}
	}
	return 0;//有必要吗
}

bool fun4(int test_array[4][4], int target) {
	int i = 0;
	int j = 4 - 1;
	while (i < 4 && j >= 0) {
		cout << i << j << endl;
		if (test_array[i][j] == target) {
			return true;
		}
		if (test_array[i][j] < target) {
			i++;
		}
		else {
			j--;
		}
	}
	return false;
}
/*int main()
{
	cout << "enter array length:" << endl;
	int length;
	cin >> length;
	int* test = new int[length];
	//int test[] = { 1,2,3,4,5,6,0 };
	cout << "enter data:" << endl;
	for (int i = 0; i < length; i++) {
		int data;
		cin >> data;
		test[i] = data;
	}
	//int length = sizeof(test) / sizeof(test[0]);
	int output1 = fun1(test, length);
	int output2 = fun2(test, length);
	cout << output1 << '\n'<< output2 << endl;
	

	cout << "enter array length(n+1):" << endl;
	int length1;
	cin >> length1;
	int* test1 = new int[length1];
	//int test[] = { 1,2,3,4,5,6,0 };
	cout << "enter data(1~n):" << endl;
	for (int i = 0; i < length1; i++) {
		int data;
		cin >> data;
		test1[i] = data;
	}
	//int length = sizeof(test) / sizeof(test[0]);
	int output3 = fun3(test1, length1);
	cout << output3 << endl;

	int test[4][4] = { {1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15} };
	cout << fun4(test,5) << endl;
	return 0;
}
*/