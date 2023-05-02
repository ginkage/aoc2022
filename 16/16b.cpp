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
vector<string> names;
vector<vector<int>> edges;
vector<int> rates;
vector<vector<int>> dists;
vector<int> flow;
vector<bool> visit;

int get_node(const string &s) {
	auto it = nodes.find(s);
	if (it == nodes.end()) {
		int node = nodes.size();
		nodes[s] = node;
		edges.emplace_back();
		rates.emplace_back();
		visit.emplace_back();
		names.push_back(s);
		return node;
	}
	return it->second;
}

int traverse(int node1, int node2, int time1, int time2, int release1, int release2, int total1, int total2, int best) {
	// Spend rest of the time chilling
	best = max(best, total1 + (26 - time1) * release1 + total2 + (26 - time2) * release2);

	for (int dst : flow)
		if (!visit[dst]) {
			// Turn on one more valve if there's still some time left
			int dt = dists[node1][dst] + 1;
			int t = time1 + dt;
			if (t < 26) {
				visit[dst] = true;
				best = max(best, traverse(node2, dst, time2, t, release2, release1 + rates[dst], total2, total1 + release1 * dt, best));
				visit[dst] = false;
			}
		}

	return best;
}

int main() {
	while (cin) {
		string s;
		getline(cin, s);
		smatch linematch;
		const regex linerex("Valve (.*) has flow rate=(.*); tunnels? leads? to valves? (.*)");
		if (regex_match(s, linematch, linerex) && linematch.size() == 4) {
			int node = get_node(linematch[1].str());
			rates[node] = stol(linematch[2].str());
			string dsts = linematch[3].str();
			stringstream ss(dsts);
			while (ss) {
				string dst;
				getline(ss, dst, ',');
				int to = get_node(dst);
				edges[node].push_back(to);
				ss.get();
			}

			if (rates[node] > 0)
				flow.push_back(node);
		}
	}

	int n = nodes.size(), start = nodes["AA"];
	dists = vector<vector<int>>(n, vector<int>(n, -1));
	for (int src = 0; src < n; src++) {
		queue<int> q;
		q.push(src);
		dists[src][src] = 0;
		while (!q.empty()) {
			int node = q.front(), dist = dists[src][node] + 1;
			q.pop();
			for (int edge : edges[node])
				if (dists[src][edge] < 0) {
					dists[src][edge] = dist;
					q.push(edge);
				}
		}
	}

	cout << traverse(start, start, 0, 0, 0, 0, 0, 0, 0) << endl;

	return 0;
} 
