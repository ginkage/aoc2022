#include <iostream>

using namespace std;

int main() {
	long x = 1, cycle = 0;
	while (true) {
		string op;
		cin >> op;
		if (!cin) break;

		if (abs(x - cycle) <= 1) cout << '#';
		else cout << '.';
		cycle = (cycle + 1) % 40;
		if (!cycle) cout << endl;

		if (op == "addx") {
			int v;
			cin >> v;
			if (abs(x - cycle) <= 1) cout << '#';
			else cout << '.';
			cycle = (cycle + 1) % 40;
			if (!cycle) cout << endl;
			x += v;
		}
	}

	return 0;
}
