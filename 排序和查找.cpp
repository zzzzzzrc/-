#include<iostream>
#include<vector>
using namespace std;

//快速排序
void QuickSort(vector<int> &nums,int len, int start, int end) {
	if (len == 1) {
		return;
	}
	int select_num = nums[end];
	int mark = start - 1;
	for (int index = start; index < end; index++) {
		if (nums[index] < select_num) {
			mark++;
			if (index != mark) {
				int temp = nums[index];
				nums[index] = nums[mark];
				nums[mark] = temp;
			}
		}
	}
	mark++;
	int temp1 = nums[mark];
	nums[mark] = nums[end];
	nums[end] = temp1;
	if (mark > start) {
		QuickSort(nums, mark - start, start, mark - 1);
	}
	if (mark < end) {
		QuickSort(nums, end - mark, mark + 1, end);
	}

}

//旋转数组中的最小值
int findMin(int* nums,int start,int end) {
	if (nums[start] < nums[end]) {
		return nums[start];
	}
	int p = start;
	int q = end;
	if (p == (q - 1)) {
		return nums[q];
	}
	int mid = (p + q) >> 1;
	if (nums[p] == nums[q] && nums[p] == nums[mid]) {
		int min_num = nums[p];
		for (int i = p; i <= q; i++) {
			if (nums[i] < min_num) {
				min_num = nums[i];
			}
		}
		return min_num;
	}
	if (nums[mid] >= nums[p]) {
		p = mid;
		findMin(nums, p,q);
	}
	else if (nums[mid] <= nums[q]) {
		q = mid;
		findMin(nums, p,q);
	}
}


int main() {
	/*vector<int> a = { 3,7,8,1,2,4,5,6 };
	int length = a.size();
	QuickSort(a, length, 0, length - 1);
	for (int i = 0; i < length; i++) {
		cout << a[i] << endl;
	}*/
	int b[] = { 1,1,0,1,1,1 };
	int output = findMin(b, 0,5);
	cout << output << endl;
}