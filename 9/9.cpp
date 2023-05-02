#include <iostream>
#include <vector>
#include <set>

using namespace std;

int sgn(int a) {
	return (a > 0) ? 1 : ((a < 0) ? -1 : 0);
}

int main() {
	set<pair<int, int>> cells;
	cells.insert(make_pair(0, 0));

	vector<pair<int, int>> knots(10, make_pair(0, 0));
	while (true) {
		string dir;
		int steps;
		cin >> dir >> steps;
		if (!cin) break;

		int dx = 0, dy = 0;
		if (dir == "U") dy = 1;
		else if (dir == "D") dy = -1;
		else if (dir == "L") dx = -1;
		else if (dir == "R") dx = 1;

		while (steps--) {
			int hx = knots[0].first, hy = knots[0].second;
			hx += dx;
			hy += dy;
			knots[0] = make_pair(hx, hy);

			for (int i = 1; i < knots.size(); i++) {
				int tx = knots[i].first, ty = knots[i].second;
				while (abs(hx - tx) > 1 || abs(hy - ty) > 1) {
					tx += sgn(hx - tx);
					ty += sgn(hy - ty);
				}
				knots[i] = make_pair(tx, ty);
				hx = tx;
				hy = ty;

			}
			cells.insert(knots.back());
		}
	}

	cout << cells.size() << endl;

	return 0;
}
