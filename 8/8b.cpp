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
	long result = 0;
	for (int i = 1; i < n-1; i++)
		for (int j = 1; j < m-1; j++) {
			long up = 0, down = 0, left = 0, right = 0;
			for (int ii = i - 1; ii >= 0; ii--) {
				up++;
				if (trees[ii][j] >= trees[i][j])
					break;
			}
			for (int ii = i + 1; ii < n; ii++) {
				down++;
				if (trees[ii][j] >= trees[i][j])
					break;
			}
			for (int jj = j - 1; jj >= 0; jj--) {
				left++;
				if (trees[i][jj] >= trees[i][j])
					break;
			}
			for (int jj = j + 1; jj < m; jj++) {
				right++;
				if (trees[i][jj] >= trees[i][j])
					break;
			}
			long score = up*down*left*right;
			result = max(result, score);
		}

	cout << result << endl;

	return 0;
}
