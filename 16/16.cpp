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

map<string, int> nodes;
vector<vector<int>> edges;
vector<int> rates;
vector<vector<int>> dists;

int get_node(const string &s) {
	cout << s << endl;
	auto it = nodes.find(s);
	if (it == nodes.end()) {
		int node = nodes.size();
		nodes[s] = node;
		edges.emplace_back();
		rates.emplace_back();
		cout << node << ' ' << s << endl;
		return node;
	}
	return it->second;
}

void hang(int src) {
	queue<int> q;
	q.push(src);
	dists[src][src] = 0;
	while (!q.empty()) {
		int node = q.front();
		q.pop();

		int dist = dists[src][node];
		for (int edge : edges[node]) {
			if (dists[src][edge] < 0) {
				dists[src][edge] = dist + 1;
				q.push(edge);
			}
		}
	}
}

int main() {
	while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        const regex linerex("Valve (.*) has flow rate=(.*); tunnels lead to valves (.*)");
        if (regex_match(s, linematch, linerex) && linematch.size() == 4) {
			int node = get_node(linematch[1].str());
			rates[node] = stol(linematch[2].str());
			string dsts = linematch[3].str();
			stringstream ss(dsts);
			while (ss) {
				string dst;
				getline(ss, dst, ',');
				if (!ss) break;
				edges[node].push_back(get_node(dst));
				ss.get();
			}
        }
    }

	int n = nodes.size();
	dists = vector<vector<int>>(n, vector<int>(n, -1));
	for (int i = 0; i < n; i++)
		hang(i);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << ' ' << dists[i][j];
		}
		cout << endl;
	}

    return 0;
} 
