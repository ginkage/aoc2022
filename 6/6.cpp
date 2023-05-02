#include <iostream>

using namespace std;

int main() {
	char buf[14];
	string s;
	cin >> s;

	for (int i = 0; i < s.size(); i++) {
		buf[i % 14] = s[i];

		if (i >= 14) {
			bool good = true;
			for (int j = 0; j < 14 && good; j++)
				for (int k = j + 1; k < 14 && good; k++)
					if (buf[j] == buf[k])
						good = false;

			if (good) {
				cout << i+1 << endl;
				break;
			}
		}
	}

	return 0;
}
