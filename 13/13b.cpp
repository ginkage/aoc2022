#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Elem {
	bool isval { false };
	long value { -1 };
	list<Elem> lst {};
};

char *parse(Elem &elem, char *str, const char *end) {
	if (str < end) {
		if (*str >= '0' && *str <= '9') {
			char *ep;
			elem.value = strtol(str, &ep, 10);
			elem.isval = true;
			str = ep;
		}
		else if (*str == '[') {
			str++;
			while (*str != ']') {
				elem.lst.emplace_back();
				str = parse(elem.lst.back(), str, end);
				if (*str == ',') str++;
			}
			str++;
		}
	}
	return str;
}

void print(Elem &elem) {
	if (elem.isval) cout << elem.value;
	else {
		cout << '[';
		bool first = true;
		for (Elem &e : elem.lst) {
			if (first) first = false;
			else cout << ',';
			print(e);
		}
		cout << ']';
	}
}

int compare(const Elem &left, const Elem &right) {
	if (left.isval && right.isval)
		return left.value - right.value;
	else if (!left.isval && !right.isval) {
		auto it = left.lst.begin(), ie = left.lst.end();
		auto jt = right.lst.begin(), je = right.lst.end();

		while (it != ie && jt != je) {
			int cmp = compare(*it, *jt);
			if (cmp != 0)
				return cmp;
			it++;
			jt++;
		}

		if (it == ie && jt != je)
			return -1;
		if (it != ie && jt == je)
			return 1;
	}
	else if (!left.isval && right.isval) {
		Elem tmp;
		tmp.lst.push_back(right);
		return compare(left, tmp);
	} else if (left.isval && !right.isval) {
		Elem tmp;
		tmp.lst.push_back(left);
		return compare(tmp, right);
	}

	return 0;
}

bool cmp(const Elem &left, const Elem &right) {
	return compare(left, right) < 0;
}

int main() {
	vector<Elem> vec;
	while (true) {
		string sl, sr;
		getline(cin, sl);
		if (!cin) break;

		vec.emplace_back();
		parse(vec.back(), (char *)sl.c_str(), sl.c_str() + sl.size());

		getline(cin, sr);
		vec.emplace_back();
		parse(vec.back(), (char *)sr.c_str(), sr.c_str() + sr.size());

		string blank;
		getline(cin, blank);
	}

	Elem val2;
	val2.isval = true;
	val2.value = 2;
	vec.emplace_back();
	vec.back().lst.emplace_back();
	vec.back().lst.back().lst.push_back(val2);

	Elem val6;
	val6.isval = true;
	val6.value = 6;
	vec.emplace_back();
	vec.back().lst.emplace_back();
	vec.back().lst.back().lst.push_back(val6);

	long index = 1, result = 1;
	sort(vec.begin(), vec.end(), cmp);
	for (Elem &elem : vec) {
		print(elem);
		cout << endl;

		if (compare(elem, val2) == 0 || compare(elem, val6) == 0)
			result *= index;
		index++;
	}

	cout << result << endl;

	return 0;
}
