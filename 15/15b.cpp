#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

int main() {
    vector<pair<pair<long, long>, pair<long, long>>> data;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        const regex linerex("Sensor at x=(.*), y=(.*): closest beacon is at x=(.*), y=(.*)");
        if (regex_match(s, linematch, linerex) && linematch.size() == 5) {
            long sx = stol(linematch[1].str()), sy = stol(linematch[2].str());
            long bx = stol(linematch[3].str()), by = stol(linematch[4].str());
            data.push_back(make_pair(make_pair(sx, sy), make_pair(bx, by)));
        }
    }

    long x1 = 0, x2 = 4000000, y1 = 0, y2 = 4000000;
    for (long ty = y1; ty <= y2; ty++) {
        vector<pair<long, long>> ivals;
        for (auto &sb : data) {
            auto s = sb.first, b = sb.second;
            long sx = s.first, sy = s.second, bx = b.first, by = b.second;
            long delta = (abs(sx - bx) + abs(sy - by)) - abs(ty - sy);
            if (delta >= 0)
                ivals.push_back(make_pair(sx - delta, sx + delta));
        }

        for (bool changed = true; changed; ) {
            changed = false;
            for (int i = 0; i < ivals.size(); i++)
                for (int j = i + 1; j < ivals.size(); j++) {
                    auto it = ivals[i], jt = ivals[j];
                    long a1 = it.first, b1 = it.second, a2 = jt.first, b2 = jt.second;
                    if (a1 <= b2+1 && a2 <= b1+1) {
                        ivals[i] = make_pair(min(a1, a2), max(b1, b2));
                        ivals[j] = ivals.back();
                        ivals.pop_back();
                        j--;
                        changed = true;
                    }
                }
        }

        if (ivals.size() > 1) {
            for (auto &p : ivals) {
                long ax = p.first, bx = p.second;
                if (ax <= x2 && x1 <= bx) {
                    long lx = max(ax, x1), rx = min(bx, x2);
                    long fx = lx == x1 ? rx + 1 : lx - 1;
                    long result = 4000000 * fx + ty;
                    cout << lx << ',' << rx << " => " << result << endl;
                }
            }
        }
    }

    return 0;
}
