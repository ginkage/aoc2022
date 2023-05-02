#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <regex>
#include <map>
#include <set>
#include <eigen3/Eigen/Core>

using namespace std;

typedef Eigen::Vector2d vec2;

int main() {
	long result = 0;
	while (cin) {
        string s;
        getline(cin, s);
		if (!cin) break;

		long num = 0;
		for (const char c : s) {
			num *= 5;
			switch (c) {
			case '=': num -= 2; break;
			case '-': num -= 1; break;
			case '0': break;
			case '1': num += 1; break;
			case '2': num += 2; break;
			}
		}

		cout << num << endl;

		result += num;
    }

	cout << result << endl;

	int num[32], nd = 0;
	for (long k = result; k; k /= 5) {
		int digit = k % 5;

		if (digit > 2) {
			digit -= 5;
			k += 5;
		}

		num[nd++] = digit;
	}

	for (int i = nd - 1; i >= 0; i--)
		if (num[i] == -2)
			cout << '=';
		else if (num[i] == -1)
			cout << '-';
		else
			cout << num[i];
	cout << endl;

    return 0;
} 
