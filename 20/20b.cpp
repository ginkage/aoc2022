#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct num {
	long val;
	num *next;
};

int main() {
	num *head = nullptr, *tail = nullptr;
	vector<num*> nums;

	while (cin) {
		long v;
		cin >> v;
		if (!cin) break;

		num *pn = new num();
		pn->val = v * 811589153;
		pn->next = nullptr;
		if (!head) head = pn;
		if (tail) tail->next = pn;
		tail = pn;

		nums.push_back(pn);
    }

	int n = nums.size();
	for (int t = 0; t < 10; t++) {
		for (num *pn = head; pn; pn = pn->next) {
			long idx = find(nums.begin(), nums.end(), pn) - nums.begin();
			long dst = idx + pn->val;
			if (dst < 0) dst += (n - 1) * (1 - dst / (n - 1));
			dst %= n - 1;
			nums.erase(nums.begin() + idx);
			nums.insert(nums.begin() + dst, pn);
		}
	}

	int zero = -1;
	for (int i = 0; i < n && zero < 0; i++)
		if (nums[i]->val == 0)
			zero = i;

	int k = (zero + 1000) % n, kk = (zero + 2000) % n, kkk = (zero + 3000) % n;
	cout << (nums[k]->val + nums[kk]->val + nums[kkk]->val) << endl;

	for (num *pn : nums)
		delete pn;

    return 0;
} 
