#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>

using namespace std;

vector<vector<pair<long, long>>> shapes = {
	{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } },
	{ { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 1, 2 } },
	{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }, { 2, 2 } },
	{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
	{ { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } }
};

string cmds;
map<long, set<long>> rows;
long ri = 0, ci = 0, height = 0;

bool busy(long x, long y) {
	if (x < 0 || x > 6 || y < 0) return true;
	auto it = rows.find(y);
	if (it == rows.end()) return false;
	auto &row = it->second;
	if (row.find(x) == row.end()) return false;
	return true;
}

bool shift(vector<pair<long, long>> &rock, long dx, long dy) {
	long good = true;
	for (auto &p : rock) {
		if (busy(p.first + dx, p.second + dy)) {
			good = false;
			break;
		}
	}

	if (good) {
		for (auto &p : rock) {
			p.first += dx;
			p.second += dy;
		}
	}

	return good;
}

void print() {
	for (long i = height; i >= 0; i--) {
		for (long j = 0; j < 7; j++)
			cout << (busy(j, i) ? '#' : '.');
		cout << endl;
	}
	cout << endl;
}

struct entry {
	unsigned long ri;
	unsigned long ci;
	long x;
	long dh;
};

int main() {
    getline(cin, cmds);

	int fh, fc, fr;

	vector<entry> history;

	while (ri < 5000) {
		vector<pair<long, long>> &shape = shapes[ri++ % shapes.size()];
		vector<pair<long, long>> rock(shape.begin(), shape.end());
		for (auto &p : rock) {
			p.first += 2;
			p.second += height + 3;
		}

		while (true) {
			char cmd = cmds[ci++ % cmds.size()];
			if (cmd == '<')
				shift(rock, -1, 0);
			else
				shift(rock, 1, 0);

			if (!shift(rock, 0, -1))
				break;
		}

		long ph = height;

		for (auto &p : rock) {
			rows[p.second].insert(p.first);
			height = max(height, p.second + 1);
		}

		entry e { (ri % shapes.size()), (ci % cmds.size()), rock[0].first, (height - ph) };
		history.push_back(e);
	}

	long hs = history.size(), hs2 = hs / 2, loop = -1;
	for (int ll = 20; ll < hs2; ll++) {
		bool good = true;
		for (int k = 0; k < ll && good; k++) {
			int i = hs - 1 - k;
			int j = i - ll;
			if (memcmp(&history[i], &history[j], sizeof(entry)) != 0)
				good = false;
		}

		if (good) {
			cout << ll << endl;
			loop = ll;
			break;
		}
	}

	long sumh = 0;
	for (int k = 0; k < loop; k++)
		sumh += history[hs - 1 - k].dh;

	long rem = 1000000000000l - ri;
	long nrep = rem / loop;
	height += sumh * nrep;
	rem %= loop;

	int i1 = hs - loop - 1, idx = i1 + 1;
	while (rem--) {
		height += history[idx].dh;
		idx++;
		if (idx >= hs)
			idx = i1;
	}

	cout << height << endl;

    return 0;
} 
