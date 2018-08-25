#include<iostream>
using namespace std;

//µÝ¹é
int fun1(int n) {
	if (n <= 0) { return 0; }
	if (n == 1) { return 1; }
	if (n >= 2) {
		return fun1(n - 1) + fun1(n - 2);
	}
}
//Ñ­»·
int fun2(int n) {
	if (n <= 0) { return 0; }
	if (n == 1) { return 1; }
	int i = 2;
	int pred = 1;
	int predpred = 0;
	int sum;
	while (i <= n) {
		sum = predpred + pred;
		predpred = pred;
		pred = sum;
		i++;
	}
	return sum;
}

int main() {
	int a = fun1(10);
	int b = fun2(10);
	cout << a << '\t' << b << endl;
	return 0;
}