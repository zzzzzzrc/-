#include<iostream>
using namespace std;

//�ж϶���������1�ĸ���  1011 �� 1 ��λ�루&��
int fun(int num) {
	int count = 0;
	unsigned int flag = 1;
	while (flag) {   //��Ҫѭ��32��
		if (num&flag) {
			count++;
		}
		flag = flag << 1;
	}
	return count;
}

int fun1(int num) { //һ������һ  �൱�����ұߵ�1��λ��Ϊ9index����Ϊ0 ��ߵ�0ȫ��Ϊ1 
	int count = 0; //index֮ǰ�������� ��ߵ�ȡ��  
	while (num) {  // ��˸�ԭ����������λ�� indexǰ�߲��� ���Ϊ0   ����൱�ڰ����ұߵ�1��Ϊ��0 ���ѭ��������� ֱ��Ϊ�����Ϊ0
		num = (num - 1)&num;  //�����Ĵ�����Ϊ ��������1�ĸ���
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