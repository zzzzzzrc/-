#include<iostream>
using namespace std;

void allorder(string str,int index)
{
	if (index == str.size() - 1)   //当分解到最后一个字符时 输出序列
	{
		for (int i = 0; i < str.size(); i++)
		{
			cout << str[i];
		}
		cout << endl;
	}
	else {
		for (int i = index; i < str.size(); i++)   //相当于固定第一位   共有n种 就也就是遍历完string每个元素都可做第一位
		{
			char temp = str[index]; 
			str[index] = str[i];
			str[i] = temp;
			allorder(str, index + 1);   //分解成子问题    第一位之后的全排列
		}
	}
}

int main()
{
	string test = "abcde";
	allorder(test, 0);
	return 0;
}