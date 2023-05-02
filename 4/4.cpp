#include <iostream>

using namespace std;

int main() {
	int result = 0;
	while (cin) {
		int a, b, c, d;
		cin >> a;
		if (!cin) break;
		cin.get();
		cin >> b;
		cin.get();
		cin >> c;
		cin.get();
		cin >> d;

//		if (a >= c && b <= d || c >= a && d <= b)
		if (a <= d && c <= b)
			result++;
	}

	cout << result << endl;

	return 0;
}
