#include <iostream>
#include <queue>
#include <regex>
#include <set>

using namespace std;

struct vec3 {
	int x, y, z;
};

bool operator < (const vec3 &l, const vec3 &r) {
	if (l.x < r.x) return true;
	if (l.x > r.x) return false;
	if (l.y < r.y) return true;
	if (l.y > r.y) return false;
	if (l.z < r.z) return true;
	return false;
}

set<vec3> drop;
set<vec3> inv;

bool find(int x, int y, int z) {
	vec3 vec { x, y, z };
	return drop.find(vec) != drop.end();
}

bool ifind(int x, int y, int z) {
	vec3 vec { x, y, z };
	return inv.find(vec) != inv.end();
}

void check(queue<vec3> &q, int x, int y, int z) {
	vec3 vec { x, y, z };
	auto it = inv.find(vec);
	if (it != inv.end()) {
		inv.erase(it);
		q.push(vec);
	}
}

int main() {
	while (cin) {
		string s;
		getline(cin, s);
		smatch match;
		const regex rex("(.*),(.*),(.*)");
		if (regex_match(s, match, rex) && match.size() == 4) {
			vec3 vec { stoi(match[1].str()), stoi(match[2].str()), stoi(match[3].str()) };
			drop.insert(vec);
		}
	}

	int result = 0;
	for (const vec3 &v : drop) {
		int ss = 6;
		if (find(v.x - 1, v.y, v.z)) ss--;
		if (find(v.x + 1, v.y, v.z)) ss--;
		if (find(v.x, v.y - 1, v.z)) ss--;
		if (find(v.x, v.y + 1, v.z)) ss--;
		if (find(v.x, v.y, v.z - 1)) ss--;
		if (find(v.x, v.y, v.z + 1)) ss--;
		result += ss;
	}

	cout << result << endl;

	for (int x = -1; x < 24; x++)
		for (int y = -1; y < 24; y++)
			for (int z = -1; z < 24; z++)
				if (!find(x, y, z)) {
					vec3 vec { x, y, z };
					inv.insert(vec);
				}

	vec3 corner { -1, -1, -1 };
	queue<vec3> q;
	q.push(corner);
	while (!q.empty()) {
		vec3 v = q.front();
		q.pop();

		check(q, v.x - 1, v.y, v.z);
		check(q, v.x + 1, v.y, v.z);
		check(q, v.x, v.y - 1, v.z);
		check(q, v.x, v.y + 1, v.z);
		check(q, v.x, v.y, v.z - 1);
		check(q, v.x, v.y, v.z + 1);
	}

	for (const vec3 &v : inv) {
		int ss = 6;
		if (ifind(v.x - 1, v.y, v.z)) ss--;
		if (ifind(v.x + 1, v.y, v.z)) ss--;
		if (ifind(v.x, v.y - 1, v.z)) ss--;
		if (ifind(v.x, v.y + 1, v.z)) ss--;
		if (ifind(v.x, v.y, v.z - 1)) ss--;
		if (ifind(v.x, v.y, v.z + 1)) ss--;
		result -= ss;
	}

	cout << result << endl;

	return 0;
}
