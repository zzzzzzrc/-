#include<iostream>
using namespace std;

void allorder(string str,int index)
{
	if (index == str.size() - 1)   //���ֽ⵽���һ���ַ�ʱ �������
	{
		for (int i = 0; i < str.size(); i++)
		{
			cout << str[i];
		}
		cout << endl;
	}
	else {
		for (int i = index; i < str.size(); i++)   //�൱�ڹ̶���һλ   ����n�� ��Ҳ���Ǳ�����stringÿ��Ԫ�ض�������һλ
		{
			char temp = str[index]; 
			str[index] = str[i];
			str[i] = temp;
			allorder(str, index + 1);   //�ֽ��������    ��һλ֮���ȫ����
		}
	}
}

int main()
{
	string test = "abcde";
	allorder(test, 0);
	return 0;
}