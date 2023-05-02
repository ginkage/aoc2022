#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Monkey {
	vector<long> items;
	long (*op)(long);
	long divisor;
	int iftrue, iffalse;
};
/*
vector<Monkey> monkeys {
	{ { 79, 98 }, [](long old) { return old * 19; }, 23, 2, 3 },
	{ { 54, 65, 75, 74 }, [](long old) { return old + 6; }, 19, 2, 0 },
	{ { 79, 60, 97 }, [](long old) { return old * old; }, 13, 1, 3 },
	{ { 74 }, [](long old) { return old + 3; }, 17, 0, 1 },
};
*/
vector<Monkey> monkeys {
	{ { 65, 58, 93, 57, 66 }, [](long old) { return old * 7; }, 19, 6, 4 },
	{ { 76, 97, 58, 72, 57, 92, 82 }, [](long old) { return old + 4; }, 3, 7, 5 },
	{ { 90, 89, 96 }, [](long old) { return old * 5; }, 13, 5, 1 },
	{ { 72, 63, 72, 99 }, [](long old) { return old * old; }, 17, 0, 4 },
	{ { 65 }, [](long old) { return old + 1; }, 2, 6, 2 },
	{ { 97, 71 }, [](long old) { return old + 8; }, 11, 7, 3 },
	{ { 83, 68, 88, 55, 87, 67 }, [](long old) { return old + 2; }, 5, 2, 1 },
	{ { 64, 81, 50, 96, 82, 53, 62, 92 }, [](long old) { return old + 5; }, 7, 3, 0 }
};

int main() {
	int n = monkeys.size();
	long gcd = 1;
	for (int i = 0; i < n; i++)
		gcd *= monkeys[i].divisor;

	vector<long> result(n, 0);
	for (int t = 0; t < 10000; t++) {
		for (int i = 0; i < n; i++) {
			Monkey &monkey = monkeys[i];
			for (long item : monkey.items) {
				result[i]++;
				long nit = monkey.op(item) % gcd;
				monkeys[(nit % monkey.divisor) == 0 ? monkey.iftrue : monkey.iffalse].items.push_back(nit);
			}

			vector<long> tmp;
			swap(monkey.items, tmp);
		}
	}

	sort(result.begin(), result.end());
	cout << result[n-1] * result[n-2] << endl;

	return 0;
}
