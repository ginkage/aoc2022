#include <iostream>

using namespace std;

int main() {
	long result = 0;
	while (!cin.eof()) {
		string a, b;
		cin >> a;
		if (!cin) break;
		cin >> b;

		int their = a[0] - 'A' + 1, win = b[0] - 'X' + 1;
		if (win == 1) {
			result += 0;
			if (their == 1) result += 3;
			else if (their == 2) result += 1;
			else result += 2;
		} else if (win == 2) {
			result += 3 + their;
		} else {
			result += 6;
			if (their == 1) result += 2;
			else if (their == 2) result += 3;
			else result += 1;
		}
	}

	cout << result << endl;

	return 0;
}
