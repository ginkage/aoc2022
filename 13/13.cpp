#include <iostream>
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

int main() {
	int index = 0, result = 0;
	while (true) {
		string sl, sr;
		getline(cin, sl);
		if (!cin) break;

		Elem left;
		const char *cl = sl.c_str(), *le = cl + sl.size();
		parse(left, (char *)cl, le);

		getline(cin, sr);
		Elem right;
		const char *cr = sr.c_str(), *re = cr + sr.size();
		parse(right, (char *)cr, re);

		string blank;
		getline(cin, blank);

		index++;
		int res = compare(left, right);
		print(left);
		cout << endl;
		print(right);
		cout << endl;
		cout << res << endl;
		if (res <= 0)
			result += index;
	}

	cout << result << endl;

	return 0;
}
