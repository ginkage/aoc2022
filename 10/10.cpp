#include <iostream>

using namespace std;

int main() {
	long result = 0;
	long x = 1;
	long cycle = 1;
	while (true) {
		string op;
		cin >> op;
		if (!cin) break;

		if (cycle >= 20 && ((cycle - 20) % 40) == 0)
			result += cycle * x;

		cycle++;
		if (op == "addx") {
			int v;
			cin >> v;

			if (cycle >= 20 && ((cycle - 20) % 40) == 0)
				result += cycle * x;
			cycle++;
			x += v;
		}
	}

	cout << result << endl;

	return 0;
}
