#include<iostream>
using namespace std;

//void swap(int &a, int &b);
void swap(int &a, int &b)
{
	int temp;
	temp = b;
	b = a;
	a = temp;
}
int main()
{
	
	int num[10] = { 5,2,7,4,6,3,1,8,10,9 };
	int i, j,temp;
	for (j = 10 - 2; j >= 0; j--)
		for (i = 0; i <= j; i++)
			if (num[i] > num[i + 1])
				swap(num[i], num[i + 1]);
	for (i=0;i<10;i++)
		cout << num[i] << endl;

	return 0;
}