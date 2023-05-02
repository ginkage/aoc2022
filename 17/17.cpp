#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>

using namespace std;

vector<vector<pair<int, int>>> shapes = {
	{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } },
	{ { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 1, 2 } },
	{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }, { 2, 2 } },
	{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
	{ { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } }
};

string cmds;
map<int, set<int>> rows;
int ri = 0, ci = 0, height = 0;

bool busy(int x, int y) {
	if (x < 0 || x > 6 || y < 0) return true;
	auto it = rows.find(y);
	if (it == rows.end()) return false;
	auto &row = it->second;
	if (row.find(x) == row.end()) return false;
	return true;
}

bool shift(vector<pair<int, int>> &rock, int dx, int dy) {
	int good = true;
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
	for (int i = height; i >= 0; i--) {
		for (int j = 0; j < 7; j++)
			cout << (busy(j, i) ? '#' : '.');
		cout << endl;
	}
	cout << endl;
}

int main() {
    getline(cin, cmds);

	while (ri < 2022) {
		vector<pair<int, int>> &shape = shapes[ri++ % shapes.size()];
		vector<pair<int, int>> rock(shape.begin(), shape.end());
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

		for (auto &p : rock) {
			rows[p.second].insert(p.first);
			height = max(height, p.second + 1);
		}

//		print();
	}

	cout << height << endl;

    return 0;
} 
