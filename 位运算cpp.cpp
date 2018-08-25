#include<iostream>
using namespace std;

//判断二进制数中1的个数  1011 与 1 按位与（&）
int fun(int num) {
	int count = 0;
	unsigned int flag = 1;
	while (flag) {   //需要循环32次
		if (num&flag) {
			count++;
		}
		flag = flag << 1;
	}
	return count;
}

int fun1(int num) { //一个数减一  相当于最右边的1（位置为9index）变为0 后边的0全变为1 
	int count = 0; //index之前的数不变 后边的取反  
	while (num) {  // 如此跟原来的数做按位与 index前边不变 后边为0   这就相当于把最右边的1变为了0 如此循环操作多次 直到为这个数为0
		num = (num - 1)&num;  //操作的次数便为 二进制中1的个数
		count++;
	}
	return count;
}
int main() {
	int a = 0x7FFFFFFF;
	int b = fun(a);
	int c = fun1(a);
	cout << b << " " << c << endl;
	return 0;
}