#include<iostream>
using namespace std;


int func(int* nums,int n)
{
	int cur_num;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (count == 0)
		{
			cur_num = nums[i];
			count = 1;
		}
		else {
			if (nums[i] == cur_num)
			{
				count++;
			}
			else {
				count--;
			}

		}
	}
	if (count > 0) {
		return cur_num;
	}
	else {
		return -1;
	}
}

int find_num(int* nums,int start, int end, int n)
{
	int mark = start - 1;
	for (int index = start; index < end; index++)
	{
		if (nums[index] < nums[end])
		{
			mark++;
			if (index != mark)
			{
				int temp = nums[index];
				nums[index] = nums[mark];
				nums[mark] = temp;
			}
		}
	}
	mark++;
	//cout << "mark" << mark << endl;
	int tmp = nums[mark];
	nums[mark] = nums[end];
	nums[end] = tmp;
	if (mark == n)
	{
		return nums[mark];
	}
	else if (mark > n)
	{
		return find_num(nums, start, mark - 1, n);
	}
	else {
		return find_num(nums, mark + 1, end, n);
	}
}

int main()
{
	int nums[5] = { 2,2,2,4,4 };
	int n = 5 / 2;
	int output = find_num(nums, 0, 4, n);
	cout << output << endl;
	int output2 = func(nums, 5);
	cout << output2 << endl;
	return 0;
}