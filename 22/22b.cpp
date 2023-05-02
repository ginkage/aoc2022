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
			int tdx = dx, tdy = dy;
			while (true) {
				if (ty < 0) {
					// tdy == -1
					if (tx < 100) {
						ty = tx + 100;
						tx = 0;
						tdx = 1;
						tdy = 0;
					}
					else {
						tx -= 100;
						ty = 199;
					}
				}
				else if (ty >= 200) {
					// tdy == 1
					tx += 100;
					ty = 0;
				}
				else if (tx < 0) {
					// tdx == -1
					if (ty < 150) {
						tx = 50;
						ty = 149 - ty;
						tdx = 1;
						tdy = 0;
					} else {
						tx = ty - 100;
						ty = 0;
						tdx = 0;
						tdy = 1;
					}
				}
				else if (tx >= 150) {
					// tdx == 1
					tx = 99;
					ty = 149 - ty;
					tdx = -1;
					tdy = 0;
				}
				else if (mmap[ty][tx] == ' ') {
					if (tdy < 0) {
						ty = tx + 50;
						tx = 50;
						tdx = 1;
						tdy = 0;
					} else if (tdx < 0) {
						if (ty < 50) {
							tx = 0;
							ty = 149 - ty;
							tdx = 1;
							tdy = 0;
						} else {
							tx = ty - 50;
							ty = 100;
							tdx = 0;
							tdy = 1;
						}
					} else if (tdy > 0) {
						if (tx < 100) {
							ty = tx + 100;
							tx = 49;
							tdx = -1;
							tdy = 0;
						} else {
							ty = tx - 50;
							tx = 99;
							tdx = -1;
							tdy = 0;
						}
					} else {
						// tdx == 1
						if (ty < 50) {
							tx = 99;
							ty = 149 - ty;
							tdx = -1;
							tdy = 0;
						}
						else if (ty < 100) {
							tx = ty + 50;
							ty = 49;
							tdx = 0;
							tdy = -1;
						}
						else if (ty < 150) {
							tx = 149;
							ty = 149 - ty;
							tdx = -1;
							tdy = 0;
						}
						else {
							tx = ty - 100;
							ty = 149;
							tdx = 0;
							tdy = -1;
						}
					}
				}
				else break;
			}

			if (mmap[ty][tx] == '#')
				break;

			x = tx;
			y = ty;
			dx = tdx;
			dy = tdy;
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
