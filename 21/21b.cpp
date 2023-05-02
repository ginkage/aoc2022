#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <regex>
#include <map>
#include <set>

using namespace std;

class monkey {
public:
	monkey(string s) : name(s) {}

	virtual long op() { return 0; }

	virtual long inverse(long res) { return res; }

	bool human() { return name == "humn"; }

	bool root() { return name == "root"; }

	virtual bool find() { return human(); }

public:
	string name;
};

map<string, monkey*> tree;

class shout : public monkey {
public:
	shout(string s, long n) : monkey(s), num(n) {}

	long op() override {
		return num;
	}

private:
	long num;
};

class wait : public monkey {
public:
	wait(string s, string s1, string s2, char c) : monkey(s), m1(s1), m2(s2), opc(c) {}

	long op() override {
		if (root()) {
			find();

			if (ha) {
				long b = tree[m2]->op();
				return tree[m1]->inverse(b);
			} else {
				long a = tree[m1]->op();
				return tree[m2]->inverse(a);
			}
		}

		long a = tree[m1]->op();
		long b = tree[m2]->op();

		switch (opc) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
		}

		return 0;
	}

	bool find() override {
		if (human()) return true;
		ha = tree[m1]->find();
		hb = tree[m2]->find();
		return ha || hb;
	}

	long inverse(long res) override {
		// res == a op b;
		if (human())
			return res;
		else if (ha) {
			long b = tree[m2]->op();
			monkey *h = tree[m1];
			switch (opc) {
				case '+': return h->inverse(res - b);
				case '-': return h->inverse(res + b);
				case '*': return h->inverse(res / b);
				case '/': return h->inverse(res * b);
			}
		} else {
			long a = tree[m1]->op();
			monkey *h = tree[m2];
			switch (opc) {
				case '+': return h->inverse(res - a);
				case '-': return h->inverse(a - res);
				case '*': return h->inverse(res / a);
				case '/': return h->inverse(a / res);
			}
		}
	}

private:
	string m1, m2;
	char opc;
	bool ha, hb;
};

int main() {
	while (cin) {
        string s;
        getline(cin, s);
        smatch match;
        if (regex_match(s, match, regex("(.*): (.*) (.) (.*)")) && match.size() == 5) {
			string monk = match[1].str();
			string s1 = match[2].str();
			char opc = match[3].str()[0];
			string s2 = match[4].str();
			tree[monk] = new wait(monk, s1, s2, opc);
        }
        else if (regex_match(s, match, regex("(.*): (.*)")) && match.size() == 3) {
			string monk = match[1].str();
			long num = stol(match[2].str());
			tree[monk] = new shout(monk, num);
        }
    }

	cout << tree["root"]->op() << endl;

    return 0;
} 
