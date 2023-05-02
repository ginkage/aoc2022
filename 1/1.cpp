#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
	vector<int> elves;
	int curelf = 0, maxelf = 0;
	while (!cin.eof()) {
		string s;
		getline(cin, s);

		if (s.size() == 0) {
			elves.push_back(curelf);
			curelf = 0;
		} else {
			curelf += stoi(s);
		}
	}

	int n = elves.size();
	sort(elves.begin(), elves.end());

	cout << elves[n-1] + elves[n-2] + elves[n-3] << endl;

	return 0;
}
