#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<vector<int>> trees;
	while (true) {
		string s;
		cin >> s;
		if (!cin) break;

		vector<int> line;
		for (char c : s)
			line.push_back(c - '0');
		trees.push_back(line);
	}

	int n = trees.size(), m = trees[0].size();
	vector<vector<bool>> vis(n, vector<bool>(m, false));

	for (int i = 0; i < n; i++) {
		int mx = -1;
		for (int j = 0; j < m; j++) {
			if (trees[i][j] > mx) {
				vis[i][j] = true;
				mx = trees[i][j];
			}
		}
		
		mx = -1;
		for (int j = m - 1; j >= 0; j--) {
			if (trees[i][j] > mx) {
				vis[i][j] = true;
				mx = trees[i][j];
			}
		}
	}

	for (int j = 0; j < m; j++) {
		int mx = -1;
		for (int i = 0; i < n; i++) {
			if (trees[i][j] > mx) {
				vis[i][j] = true;
				mx = trees[i][j];
			}
		}
		
		mx = -1;
		for (int i = n - 1; i >= 0; i--) {
			if (trees[i][j] > mx) {
				vis[i][j] = true;
				mx = trees[i][j];
			}
		}
	}

	int result = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (vis[i][j])
				result++;
	cout << result << endl;

	return 0;
}
