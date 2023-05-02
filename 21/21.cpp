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
	virtual long op() { return 0; }
};

map<string, monkey*> tree;

class shout : public monkey {
public:
	shout(long n) : num(n) {}

	long op() override {
		return num;
	}

private:
	long num;
};

class wait : public monkey {
public:
	wait(string s1, string s2, char c) : m1(s1), m2(s2), opc(c) {}

	long op() override {
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

private:
	string m1, m2;
	char opc;
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
			tree[monk] = new wait(s1, s2, opc);
        }
        else if (regex_match(s, match, regex("(.*): (.*)")) && match.size() == 3) {
			string monk = match[1].str();
			long num = stol(match[2].str());
			tree[monk] = new shout(num);
        }
    }

	cout << tree["root"]->op() << endl;

    return 0;
} 
