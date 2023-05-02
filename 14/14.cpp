#include <iostream>
#include <sstream>
#include <set>

using namespace std;

int sign(int x) {
	return (x < 0 ? -1 : (x > 0 ? 1 : 0));
}

int main() {
	set<pair<int,int>> slice;

	int my = -1;
	while (true) {
		string s;
		getline(cin, s);
		if (!cin) break;

		int sx = -1, sy = -1;
		stringstream ss(s);
		while (ss) {
			int x, y;
			ss >> x;
			ss.get();
			ss >> y;
			my = max(my, y);

			if (sx < 0 || sy < 0) {
				sx = x;
				sy = y;
				slice.insert(make_pair(sx, sy));
			}
			else {
				while (sx != x || sy != y) {
					slice.insert(make_pair(sx, sy));
					sx += sign(x - sx);
					sy += sign(y - sy);
				}
				slice.insert(make_pair(sx, sy));
			}

			if (ss.peek() == ' ') {
				ss.get();
				ss.get();
				ss.get();
				ss.get();
			}
			else
				break;
		}
	}

	int count = 0;
	while (++count) {
		int x = 500, y = 0;
		while (y <= my) {
			if (slice.find(make_pair(x, y+1)) == slice.end())
				y++;
			else if (slice.find(make_pair(x-1, y+1)) == slice.end()) {
				x--;
				y++;
			}
			else if (slice.find(make_pair(x+1, y+1)) == slice.end()) {
				x++;
				y++;
			}
			else
				break;
		}
		slice.insert(make_pair(x, y));

//		if (y > my) break;
		if (x == 500 && y == 0)
			break;
	}

	cout << count << endl;

	return 0;
}
