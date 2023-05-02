#include <iostream>
#include <unordered_set>
#include <map>
#include <string>

using namespace std;

int main() {
	long result = 0;
	int idx = 0;
	map<char, int> trifreq;
	while (cin) {
		string s;
		cin >> s;
		int n = s.size();
		if (n <= 0)
			break;

		unordered_set<char> ss;
		for (int i = 0; i < n; i++)
			trifreq[s[i]] |= (1 << idx);

		idx++;
		if (idx == 3) {
			for (auto &p : trifreq) {
				if (p.second == 7) {
					result += (p.first < 'a') ? (p.first - 'A' + 27) : (p.first - 'a' + 1);
					cout << p.first << endl;
					break;
				}
			}

			map<char, int> nil;
			swap(trifreq, nil);
			idx = 0;
		}
	}
	cout << result << endl;
	return 0;
}
