#include<iostream>
#include<vector>
using namespace std;

bool find_path(vector<vector<char>> array, string target, int index, vector<vector<int>> &reached_path,int i,int j) {
	int row = array.size();
	int col = array[0].size();
	if (i < 0 || i >= row || j < 0 || j >= col||reached_path[i][j]==1) {   //�߽�����  �Լ��������Ĳ��ٱ���
		return false;
	}
	if ((index == target.length() - 1) && (array[i][j] == target[index])) { //�������ĳ��������target���һ���ַ���Ӧ-->����path
		return true;
	}
	if (array[i][j] != target[index]) {//��ǰ�����ĳ����target��Ӧ���ַ�����Ӧ
		return false;
	}
	else {
		reached_path[i][j] = 1;   //�����Ӧ  ���������   ����������������   ֻҪ��һ�������return true
		return find_path(array, target, index + 1, reached_path, i - 1, j) ||
			find_path(array, target, index + 1, reached_path, i + 1, j) ||
			find_path(array, target, index + 1, reached_path, i, j - 1) ||
			find_path(array, target, index + 1, reached_path, i, j + 1);
	}
}

bool path_in_array(vector<vector<char>> array, string target) {
	int row = array.size();
	int col = array[0].size();
	vector<vector<int>> reached_path(row,vector<int>(col));  //��άvector�ĸ�ֵ
	for(int i=0;i<row;i++)
		for (int j = 0; j < col; j++) {
			reached_path[i].push_back(0);
		}
	for(int r=0;r<row;r++)
		for (int c = 0; c < col; c++) {
			cout << "start: "<< array[r][c] << endl;
			if (reached_path[r][c] == 0) {
				if (find_path(array, target, 0, reached_path, r, c)) {
					return true;
				}
			}
		}
	return false;

}

int main()
{
	vector<vector<char>> test = { {'a','b','t','g'},
								  {'c','f','c','s'},
								  {'j','d','e','h'} };
	string target = "hscb";
	bool output = path_in_array(test, target);
	cout << output << endl;
	return 0;
}
