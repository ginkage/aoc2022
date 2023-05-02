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

int main() {
	vector<vector<char>> mmap;

	int startx = 0, m = 0;
	while (cin) {
        string s;
        getline(cin, s);
		if (s.size() == 0) break;

		vector<char> row(s.size(), ' ');

		int x = 0;
		for (const char c : s) {
			if (c == '.' && !startx)
				startx = x;
			row[x++] = c;
		}

		m = max(m, x);
		mmap.push_back(row);
    }

	for (vector<char> &v : mmap)
		while (v.size() < m)
			v.push_back(' ');

	string s;
    getline(cin, s);
	stringstream ss(s);

	int x = startx, y = 0, dx = 1, dy = 0;
	while (ss) {
		int step;
		ss >> step;

		for (int t = 0; t < step; t++) {
			int tx = x + dx, ty = y + dy;
			while (true) {
				if (ty < 0)
					ty = mmap.size() - 1;
				else if (ty >= mmap.size())
					ty = 0;
				else if (tx < 0)
					tx = mmap[ty].size() - 1;
				else if (tx >= mmap[ty].size())
					tx = 0;
				else if (mmap[ty][tx] == ' ') {
					tx += dx;
					ty += dy;
				}
				else break;
			}

			if (mmap[ty][tx] == '#')
				break;

			x = tx;
			y = ty;
		}

		char dir = ss.get();
		if (ss) {
			if (dir == 'L') {
				int tmp = dy;
				dy = -dx;
				dx = tmp;
			} else {
				int tmp = dy;
				dy = dx;
				dx = -tmp;
			}
		}
	}

	int dir = (dx > 0) ? 0 : ((dy > 0) ? 1 : ((dx < 0) ? 2 : 3));
	cout << (1000*(y+1) + 4*(x+1) + dir) << endl;

    return 0;
} 
