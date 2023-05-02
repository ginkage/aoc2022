#include <iostream>
#include <unordered_set>
#include <set>
#include <string>

using namespace std;

int main() {
	long result = 0;
	int idx = 0;
	while (cin) {
		string s;
		cin >> s;
		int n = s.size(), n2 = n/2;
		if (n <= 0)
			break;

		unordered_set<char> ss;
		for (int i = 0; i < n; i++) {
			if (i < n2)
				ss.insert(s[i]);
			else if (ss.find(s[i]) != ss.end()) {
				cout << s[i] << endl;
				result += (s[i] < 'a') ? (s[i] - 'A' + 27) : (s[i] - 'a' + 1);
				break;
			}
		}
	}
	cout << result << endl;
	return 0;
}
