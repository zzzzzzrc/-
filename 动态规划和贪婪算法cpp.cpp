#include<iostream>
using namespace std;

//割绳子问题  长为n的绳子，分成m段m>1 各小段的乘积最大  
//分解成子问题  f(n) = max(f(i)*f(n-i))  长为i的最大值×长为n-i的最大值

//动态规划解决
int maxProduct(const int length)
{
	if (length == 1) { return 0; }
	if (length == 2) { return 1; }
	if (length == 3) { return 2; } // 长度为3的绳子 切两端   最大乘积为2   长度大于3 时 ，若切出的子绳子长度为3  无需再切  最大为3
	int* product = new int[length+1];  //乘积的最优值
	string* item = new string[length + 1];  //该乘积是由那些数组成
	product[0] = 0;
	product[1] = 1;
	product[2] = 2;
	product[3] = 3;
	item[0] = "0";
	item[1] = "1";
	item[2] = "2";
	item[3] = "3";
	int max_product = 0;
	int index1 = 0;
	int index2 = 0;
	for (int i = 4; i <= length; i++) 
	{
		max_product = 0;
		index1 = 0;
		index2 = 0;
		for (int j = 1; j <= i / 2; j++)
		{
			int cur_product = product[j] * product[i - j];
			if (cur_product > max_product) {
				max_product = cur_product;
				index1 = j;   
				index2 = i - j;
			}
		}
		product[i] = max_product;
		item[i] = item[index1] + item[index2];   //乘积为product[j]的那些数+乘积为product[i-j]的那些数。
	}
	int output = product[length];
	string len = item[length];
	for (int i = 0; i < len.size(); i++) {
		cout << "length:" << len[i] << endl;
	}
	delete [] product;
	return output;
}


//接下来是贪婪算法
//多分割一些长度为3的  当剩下的长度为4时 分为2×2

int main() {
	int length = 8;
	int max_product = maxProduct(length);
	cout << "max_product:" << max_product << endl;
	return 0;
}