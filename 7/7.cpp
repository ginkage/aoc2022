#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

struct folder {
	map<string, long> files;
	map<string, folder> subdirs;
	folder *parent { nullptr };
	long total { 0 };
};

long result = 0, result2 = 70000000, freespace = 0;

long fold(folder *dir) {
	for (auto it = dir->subdirs.begin(), end = dir->subdirs.end(); it != end; it++)
		dir->total += fold(&it->second);
	for (auto it = dir->files.begin(), end = dir->files.end(); it != end; it++)
		dir->total += it->second;
	if (dir->total <= 100000)
		result += dir->total;
	return dir->total;
}

void fold2(folder *dir) {
	for (auto it = dir->subdirs.begin(), end = dir->subdirs.end(); it != end; it++)
		fold2(&it->second);
	long free = freespace + dir->total;
	if (free >= 30000000)
		result2 = min(result2, dir->total);
}

int main() {
	folder root;
	folder *curdir = &root;

	while (true) {
		string s;
		getline(cin, s);
		if (!cin) break;

		stringstream ss(s);
		if (s[0] == '$') {
			ss.get();
			ss.get();

			string cmd;
			ss >> cmd;
			if (cmd == "cd") {
				string dir;
				ss.get();
				getline(ss, dir);

				if (dir == "..")
					curdir = curdir->parent;
				else if (dir == "/")
					curdir = &root;
				else
					curdir = &(curdir->subdirs[dir]);
			}
		} else {
			string prefix, file;
			ss >> prefix;
			ss.get();
			getline(ss, file);

			if (prefix == "dir") {
				curdir->subdirs[file].parent = curdir;
			} else {
				curdir->files[file] = stoi(prefix);
			}
		}
	}

	freespace = 70000000 - fold(&root);
	fold2(&root);
	cout << result << " " << result2 << endl;

	return 0;
}
