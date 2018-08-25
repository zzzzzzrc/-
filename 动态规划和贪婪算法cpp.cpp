#include<iostream>
using namespace std;

//����������  ��Ϊn�����ӣ��ֳ�m��m>1 ��С�εĳ˻����  
//�ֽ��������  f(n) = max(f(i)*f(n-i))  ��Ϊi�����ֵ����Ϊn-i�����ֵ

//��̬�滮���
int maxProduct(const int length)
{
	if (length == 1) { return 0; }
	if (length == 2) { return 1; }
	if (length == 3) { return 2; } // ����Ϊ3������ ������   ���˻�Ϊ2   ���ȴ���3 ʱ �����г��������ӳ���Ϊ3  ��������  ���Ϊ3
	int* product = new int[length+1];  //�˻�������ֵ
	string* item = new string[length + 1];  //�ó˻�������Щ�����
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
		item[i] = item[index1] + item[index2];   //�˻�Ϊproduct[j]����Щ��+�˻�Ϊproduct[i-j]����Щ����
	}
	int output = product[length];
	string len = item[length];
	for (int i = 0; i < len.size(); i++) {
		cout << "length:" << len[i] << endl;
	}
	delete [] product;
	return output;
}


//��������̰���㷨
//��ָ�һЩ����Ϊ3��  ��ʣ�µĳ���Ϊ4ʱ ��Ϊ2��2

int main() {
	int length = 8;
	int max_product = maxProduct(length);
	cout << "max_product:" << max_product << endl;
	return 0;
}