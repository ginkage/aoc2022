#include <iostream>

using namespace std;

int main() {
	long result = 0;
	while (!cin.eof()) {
		string a, b;
		cin >> a;
		if (!cin) break;
		cin >> b;

		int their = a[0] - 'A' + 1, my = b[0] - 'X' + 1;
		result += my;
		if (my == their)
			result += 3;
		else if (my == 1 && their == 2 || my == 2 && their == 3 || my == 3 && their == 1)
			result += 0;
		else
			result += 6;

		cout << my << ' ' << their << endl;
	}

	cout << result << endl;

	return 0;
}
