#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>

using namespace std;

typedef pair<int, int> elf;

set<elf> elves;

typedef vector<pair<int, int>> dir;

const vector<dir> dirs = {
	{ { -1, -1 }, { -1, 0 }, { -1, 1 } },
	{ { 1, -1 }, { 1, 0 }, { 1, 1 } },
	{ { -1, -1 }, { 0, -1 }, { 1, -1 } },
	{ { -1, 1 }, { 0, 1 }, { 1, 1 } }
};

static inline bool find(const elf p) {
	return elves.find(p) != elves.end();
}

static inline bool has_near(const elf &p) {
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (i || j)
				if (find(make_pair(p.first + i, p.second + j)))
					return true;
	return false;
}

static inline bool vacant(const elf &p, const dir &d) {
	for (auto &t : d)
		if (find(make_pair(p.first + t.first, p.second + t.second)))
			return false;
	return true;
}

void print() {
	auto it = elves.begin();
	int cmin = it->second, cmax = it->second, rmin = it->first, rmax = it->first;
	for (const elf &e : elves) {
		cmin = min(cmin, e.second);
		cmax = max(cmax, e.second);
		rmin = min(rmin, e.first);
		rmax = max(rmax, e.first);
	}

	for (int r = rmin; r <= rmax; r++) {
		for (int c = cmin; c <= cmax; c++)
			cout << (find(make_pair(r, c)) ? "#" : ".");
		cout << endl;
	}
	cout << ((rmax - rmin + 1) * (cmax - cmin + 1) - elves.size()) << endl;
}

int main() {
	int row = 0;
	while (cin) {
        string s;
        getline(cin, s);
		if (!cin) break;

		for (int col = 0; col < s.size(); col++)
			if (s[col] == '#')
				elves.insert(make_pair(row, col));
		row++;
    }

	print();

	int t = 0;
	bool any_moved = true;
	while (any_moved) {
		any_moved = false;
		set<elf> next;
		map<elf, vector<elf>> target;

		for (const elf &e : elves) {
			if (has_near(e)) {
				bool moved = false;
				for (int i = 0; i < 4 && !moved; i++) {
					const dir &d = dirs[(i + t) % 4];
					if (vacant(e, d)) {
						elf consid = make_pair(e.first + d[1].first, e.second + d[1].second);
						target[consid].push_back(e);
						moved = true;
					}
				}

				if (!moved)
					next.insert(e);
			}
			else
				next.insert(e);
		}

		for (auto &p : target) {
			if (p.second.size() == 1) {
				next.insert(p.first);
				any_moved = true;
			}
			else
				for (const elf &e : p.second)
					next.insert(e);
		}

		swap(elves, next);
		print();
		t++;
	}

	cout << t << endl;

    return 0;
} 
