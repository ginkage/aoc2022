#include <iostream>
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

bool find(int x, int y, int z) {
	vec3 vec { x, y, z };
	return drop.find(vec) != drop.end();
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

	return 0;
}
