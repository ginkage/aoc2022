#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>

using namespace std;

int m = 0, n = 0;
map<pair<int, int>, vector<char>> blizz;

void print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			auto c = make_pair(i, j);
			auto it = blizz.find(c);
			if (it == blizz.end())
				cout << '.';
			else if (it->second.size() == 1)
				cout << it->second[0];
			else cout << it->second.size();
		}
		cout << endl;
	}
	cout << endl;
}

void clamp(pair<int, int> &p) {
	if (p.first < 0) p.first = n - 1;
	if (p.first >= n) p.first = 0;
	if (p.second < 0) p.second = m - 1;
	if (p.second >= m) p.second = 0;
}

void step() {
	map<pair<int, int>, vector<char>> next;

	for (auto &b : blizz) {
		auto p = b.first;
		for (const char c : b.second) {
			pair<int, int> np = p;
			switch (c) {
				case '<': np.second--; break;
				case '^': np.first--; break;
				case 'v': np.first++; break;
				case '>': np.second++; break;
			}
			clamp(np);
			next[np].push_back(c);
		}
	}

	swap(blizz, next);
}

int main() {
	string s;
	getline(cin, s);

	m = s.size() - 2;
	while (cin) {
		getline(cin, s);
		if (!cin) break;
		if (s[1] == '#') break;

		for (int col = 1; col <= s.size(); col++) {
			switch (s[col]) {
				case '<': case '^': case 'v': case '>':
					blizz[make_pair(n, col-1)].push_back(s[col]);
					break;
			}
		}
		n++;
    }

	set<pair<int, int>> pos;
	pos.insert(make_pair(-1, 0));
	bool found = false;
	int trip = 0;
	for (int t = 1; !found; t++) {
		set<pair<int, int>> next;
		step();

		for (auto &p : pos) {
			if (p.first > 0) {
				pair<int, int> np = make_pair(p.first - 1, p.second);
				if (blizz.find(np) == blizz.end())
					next.insert(np);
			}
			if (p.first < n - 1) {
				pair<int, int> np = make_pair(p.first + 1, p.second);
				if (blizz.find(np) == blizz.end())
					next.insert(np);
			}
			if (p.second > 0 && p.first != -1 && p.first != n) {
				pair<int, int> np = make_pair(p.first, p.second - 1);
				if (blizz.find(np) == blizz.end())
					next.insert(np);
			}
			if (p.second < m - 1 && p.first != -1 && p.first != n) {
				pair<int, int> np = make_pair(p.first, p.second + 1);
				if (blizz.find(np) == blizz.end())
					next.insert(np);
			}

			if (blizz.find(p) == blizz.end())
				next.insert(p);

			if ((trip == 1 && p.first == 0 && p.second == 0) ||
				((trip == 0 || trip == 2) && p.first == n - 1 && p.second == m - 1)) {
				cout << t << endl;
				found = true;
				break;
			}
		}

		if (found) {
			if (trip == 0) {
				set<pair<int, int>> finish;
				finish.insert(make_pair(n, m - 1));
				swap(pos, finish);
				found = false;
			}
			else if (trip == 1) {
				set<pair<int, int>> start;
				start.insert(make_pair(-1, 0));
				swap(pos, start);
				found = false;
			}
			trip++;
		}
		else
			swap(pos, next);
	}

    return 0;
} 
