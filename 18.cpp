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
	while (cin) {
        string s;
        getline(cin, s);
        smatch match;
        const regex rex("(.*)");
        if (regex_match(s, match, rex) && match.size() == 4) {
			string str = match[1].str();
        }
    }

    return 0;
} 
