#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <regex>
#include <map>
#include <set>

using namespace std;

struct num {
	int val;
	num *next;
};

int main() {
	num *head = nullptr, *tail = nullptr;
	vector<num*> nums;

	while (cin) {
		int v;
		cin >> v;
		if (!cin) break;

		num *pn = new num();
		pn->val = v;
		pn->next = nullptr;
		if (!head) head = pn;
		if (tail) tail->next = pn;
		tail = pn;

		nums.push_back(pn);
    }

	int n = nums.size();

	for (num *pn = head; pn; pn = pn->next) {
		int idx = find(nums.begin(), nums.end(), pn) - nums.begin();
		int dst = idx + pn->val;
		while (dst < 0) dst += n - 1;
		dst %= n - 1;
/*
		for (num *pr : nums)
			cout << ' ' << pr->val;
		cout << endl;
		cout << idx << " + " << pn->val << " = " << dst << endl;
*/
		nums.erase(nums.begin() + idx);
		nums.insert(nums.begin() + dst, pn);
	}
/*
	for (num *pn : nums) {
		cout << ' ' << pn->val;
		delete pn;
	}
	cout << endl;
*/
	int zero = -1;
	for (int i = 0; i < n && zero < 0; i++)
		if (nums[i]->val == 0)
			zero = i;

	int k = (zero + 1000) % n, kk = (zero + 2000) % n, kkk = (zero + 3000) % n;
	cout << nums[k]->val << ' ' << nums[kk]->val << ' ' << nums[kkk]->val << endl;
	cout << (nums[k]->val + nums[kk]->val + nums[kkk]->val) << endl;

	for (num *pn : nums)
		delete pn;

    return 0;
} 
