#include<iostream>
using namespace std;

bool add(char* num)
{
	int length = strlen(num);
	int carry = 0;
	for (int i = length - 1; i >= 0; i--) {
		int nSum = num[i] - '0' + carry;
		carry = 0;
		if (i == length - 1) {   //从最后一位开始
			nSum++;				//+1
		}
		if (nSum >= 10) {     //+1后需要进位
			if (i == 0) {
				return false;   //最高位需要进位
			}
			nSum = nSum - 10;  //进位后该位的数
			carry = 1;
			num[i] = '0' + nSum;
		}
		else {
			num[i] = '0' + nSum;
			//cout <<"hh"<< num[i] << endl;
			break;
		}
	}
	return true;
}


void print(char* num) {
	int length = strlen(num);
	bool begin = false;
	//string output = "";
	for (int i = 0; i < length; i++) {
		if (num[i] != '0') {
			begin = true;
		}
		if (begin) {
			cout << num[i];
		}
	}
	cout << endl;
}
void Print1ToMaxn(int n)
{
	if (n <= 0) { return; }
	char* num = new char[n + 1];
	for (int i = 0; i < n; i++) {
		num[i] = '0';
	}
	num[n] = '\0';
	while (add(num)) {
		print(num);
	}
}

//递归操作
bool set(char* num, int index, int carry) {
	int nSum = num[index] - '0' + carry;
	if (carry == 0) { nSum++; }
	carry = 0;
	if (nSum >= 10) {
		if (index == 0) { return false; }
		nSum = nSum - 10;
		carry = 1;
		num[index] = '0' + nSum;
		return set(num, index - 1, carry);
	}
	else {
		num[index] = '0'+nSum;
		return true;
	}
}

void Print1ToMaxn_1(int n)
{
	if (n <= 0) { return; }
	char* num = new char[n + 1];
	for (int i = 0; i < n; i++) {
		num[i] = '0';
	}
	num[n] = '\0';
	while (set(num,n-1,0)) {
		print(num);
	}
}

int main() {
	int n = 2;
	Print1ToMaxn_1(n);
	return 0;
}