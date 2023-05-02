#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
	long ty = 2000000;

	vector<pair<long,long>> ivals;
	while (true) {
		string s;
		getline(cin, s);
		if (!cin) break;

		long bx, by, sx, sy;
		string tmp;
		stringstream ss(s);
		ss >> tmp;
		if (!cin) break;
		ss >> tmp;
		ss.get();
		ss.get();
		ss.get();

		ss >> sx;
		ss.get();
		ss.get();
		ss.get();
		ss.get();
		ss >> sy;

		ss.get();
		ss >> tmp;
		ss >> tmp;
		ss >> tmp;
		ss >> tmp;
		ss.get();
		ss.get();
		ss.get();

		ss >> bx;
		ss.get();
		ss.get();
		ss.get();
		ss.get();
		ss >> by;

		long delta = abs(sx - bx) + abs(sy - by);
		long dd = delta - abs(sy - ty);
		if (dd >= 0) {
			long x1 = sx - dd, x2 = sx + dd;
			ivals.push_back(make_pair(x1, x2));
		}
	}

	for (int i = 0; i < ivals.size(); i++) {
		for (int j = i + 1; j < ivals.size(); j++) {
			long a1 = ivals[i].first, b1 = ivals[i].second;
			long a2 = ivals[j].first, b2 = ivals[j].second;
			if (a1 <= b2 && a2 <= b1) {
				long a = min(a1, a2), b = max(b1, b2);
				ivals[i].first = a;
				ivals[i].second = b;
				ivals[j] = ivals.back();
				ivals.pop_back();
				j--;
			}
		}
	}

	long result = 0;
	for (int i = 0; i < ivals.size(); i++) {
		cout << ivals[i].first << ',' << ivals[i].second << endl;
		result += ivals[i].second - ivals[i].first + 1;
	}

	cout << (result - 1) << endl;

	return 0;
}
