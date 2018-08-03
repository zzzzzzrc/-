#include<iostream>
#include<ctime>
#include<Windows.h>
using namespace std;
int fib1(int n)
{
	if (n == 1 or n == 2)
	{
		return 1;
	}
	else
	{
		return (fib1(n - 1) + fib1(n - 2));
	}
}

int fib2(int n, int prevprev, int prev) 
{
	if (n <= 2)
	{
		return prev;
	}
	else
	{
		return fib2(n - 1, prev, prevprev + prev);
	}

}

int fib3(int n, int& prev)
{
	if (n == 0)
	{
		prev = 1;
		return 0;
	}
	else
	{
		int prevprev;
		prev = fib3(n - 1, prevprev);
		return prevprev + prev;
	}
}
int main()
{
	int a = 1;
	DWORD start_time1 = GetTickCount();
	for (int i = 1; i < 1000000; i++)
		fib1(5);
	DWORD end_time1 = GetTickCount();
	cout << "The run time is:" << (end_time1 - start_time1) << "ms!" << endl;//输出运行时间
	DWORD start_time2 = GetTickCount();
	for (int i = 1; i<1000000; i++)
		fib2(5,1,1);
	DWORD end_time2 = GetTickCount();
	cout << "The run time is:" << (end_time2 - start_time2) << "ms!" << endl;//输出运行时间
	DWORD start_time3 = GetTickCount();
	for (int i = 1; i < 1000000; i++)
		fib3(5, a);
	DWORD end_time3 = GetTickCount();
	cout << "The run time is:" << (end_time3 - start_time3) << "ms!" << endl;//输出运行时间
	return 0;
}