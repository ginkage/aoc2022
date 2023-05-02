#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	vector<vector<int>> height;
	int sx, sy, ex, ey;
	while (true) {
		string s;
		cin >> s;
		if (!cin) break;

		int n = s.size();
		vector<int> row(n);
		for (int i = 0; i < n; i++) {
			if (s[i] == 'S') {
				sx = i;
				sy = height.size();
				row[i] = 0;
			} else if (s[i] == 'E') {
				ex = i;
				ey = height.size();
				row[i] = 25;
			} else
				row[i] = s[i] - 'a';
		}
		height.push_back(row);
	}

	int n = height.size(), m = height[0].size();
	vector<vector<int>> dist(n, vector<int>(m, m * n + 1));
	queue<pair<int, int>> q;

	dist[ey][ex] = 0;
	q.push(make_pair(ey, ex));

	while (!q.empty()) {
		auto p = q.front();
		int i = p.first, j = p.second;
		int d = dist[i][j], h = height[i][j];
		q.pop();

		if (h == 0) {
			cout << d << endl;
			break;
		}

		if (i > 0 && (d + 1) < dist[i-1][j] && (h - 1) <= height[i-1][j]) {
			dist[i-1][j] = d + 1;
			q.push(make_pair(i-1, j));
		}
		if (j > 0 && (d + 1) < dist[i][j-1] && (h - 1) <= height[i][j-1]) {
			dist[i][j-1] = d + 1;
			q.push(make_pair(i, j-1));
		}
		if (i < n-1 && (d + 1) < dist[i+1][j] && (h - 1) <= height[i+1][j]) {
			dist[i+1][j] = d + 1;
			q.push(make_pair(i+1, j));
		}
		if (j < m-1 && (d + 1) < dist[i][j+1] && (h - 1) <= height[i][j+1]) {
			dist[i][j+1] = d + 1;
			q.push(make_pair(i, j+1));
		}
	}

	return 0;
}
