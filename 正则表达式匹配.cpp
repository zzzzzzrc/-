#include<iostream>
using namespace std;

bool match(char* target, char* mod,int index1, int index2)
{
	int target_len = strlen(target);
	int mod_len = strlen(mod);
	if (index1 == target_len && index2 == mod_len) {
		return true;
	}
	if (index1 == target_len && index2 < mod_len) {
		if (mod[index2 + 1] == '*')
			return match(target, mod, index1, index2 + 2);
		else {
			return false;
		}
	}
	if (index1 < target_len && index2 == mod_len) {
		return false;
	}
	if ((index2 < (mod_len - 1)) && (mod[index2 + 1] == '*'))
	{
		if (target[index1] != mod[index2]) {
			return match(target, mod, index1, index2 + 2);
		}
		else {
			return match(target, mod, index1 + 1, index2) || match(target, mod, index1, index2 + 2);
		}
	}
	if (mod[index2 + 1] != '*') {
		if (mod[index2] == '.') {
			return match(target, mod, index1 + 1, index2 + 1);
		}
		else {
			if (target[index1] == mod[index2]) {
				return  match(target, mod, index1 + 1, index2 + 1);
			}
			else {
				return false;
			}
		}
	}
}

int main() {
	char target[] = "a";
	char mod[] = "ab*a*c*";
	cout << match(target, mod, 0, 0)<<endl;
	return 0;
}