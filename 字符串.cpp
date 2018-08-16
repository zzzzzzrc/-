#include<iostream>
using namespace std;
int shift(int i, int len, char* array)
{
	for (int n = len-1; n > i; n--) {
		array[n + 2] = array[n];
	}
	array[i] = '%';
	array[i + 1] = '2';
	array[i + 2] = '0';
	len += 2;
	return len;
}

// 遍历一遍遇到空格就把后面的移位 并加入%20
char* fun1(char* test) {
	int i = 0;
	int j = 0;
	int length = 1;
	while (test[i] != '\0') {
		length++;
		i++;
	}
	while (test[j] != '\0') {
		if (test[j] == ' ') {
			length = shift(j, length, test);
			j += 3;
		}
		else {
			j++;
		}
	}
	cout << test << endl;
	return test;
}

char* fun2(char* array) {
	int i = 0;
	int blank_count = 0;
	int length = 1;
	while (array[i] != '\0') {   //得到字符串的长度 以及空格的个数
		if (array[i] == ' ') {
			blank_count += 1;
		}
		length += 1;
		i++;
	}
	int p = length - 1;
	int q = length + blank_count * 2 - 1;
	while (p < q) {
		if (array[p] != ' ') {
			array[q] = array[p];
			p--;
			q--;
		}
		else {
			array[q] = '0';
			array[q - 1] = '2';
			array[q - 2] = '%';  
			q = q - 3;
			p--;
		}
	}
	//cout << array << endl;
	return array;
}

/*int main() {
	char test[100] = "1 2 2 3 ";
	char* output = fun2(test);
	cout << output << endl;
}*/