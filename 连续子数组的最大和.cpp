#include<iostream>
using namespace std;

int max_subaray_sum(int* nums,int n)
{
	if (nums == nullptr)
	{
		return 0;
	}
	int cur_sum = nums[0];
	int last_sum = cur_sum;
	int cur_max=cur_sum;
	for (int i = 1; i < n; i++)
	{
		if (last_sum < 0) {
			cur_sum = nums[i];
			last_sum = cur_sum;
		}
		else {
			cur_sum = last_sum + nums[i];
			if (cur_sum > cur_max) {
				cur_max = cur_sum;
			}
			last_sum = cur_sum;
		}
	}

	return cur_max;
}

int main() {
	int nums[] = { 1,-2,3,10,-4,7,2,-5 };
	int max_sum = max_subaray_sum(nums, 8);
	cout << max_sum << endl;
	return 0;
}