#include<iostream>
#include<vector>
using namespace std;

int fun(int m, int n, int i, int j, int k,vector<vector<int>> &array) {
	//cout << i << j << endl;
	if (i < 0 || i >= m || j < 0 || j >= n || array[i][j]==1) {
		return 0;
	}
	int sum_bit = 0;
	int row = i;
	int col = j;
	while (row != 0) {
		sum_bit += row % 10;
		row = row / 10;
	}
	while (col != 0) {
		sum_bit += col % 10;
		col = col / 10;
	}
	if (sum_bit > k) {
		return 0;
	}
	else {
		cout << i << j << endl;
		array[i][j] = 1;
		return 1 + fun(m, n, i + 1, j, k, array) + 
			fun(m, n, i - 1, j, k, array) + 
			fun(m, n, i, j + 1, k, array) + 
			fun(m, n, i, j - 1, k, array);
	}
}

int movingCount(int m, int n, int k)  // m行n列 坐标数位和不超过k
{
	vector<vector<int>> array(m, vector<int>(n));
	for(int i=0;i<m;i++)
		for (int j = 0; j < n; j++) {
			array[i][j] = 0;
		}
	int count = fun(m, n, 0, 0, k, array);
	return count;
}

/*int main() {
	int m = 2;
	int n = 2;
	int k = 2;
	int output = movingCount(m, n, k);
	cout << output << endl;
	return 0;
}*/