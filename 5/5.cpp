#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    vector<stack<char>> stacks(9);
    for (int i = 0; i < 8; i++) {
        string s;
        getline(cin, s);

        for (int j = 0; j < 9; j++) {
            char c = s[4*j + 1];
            if (c != ' ')
                stacks[j].push(c);
        }
    }

    for (int j = 0; j < 9; j++) {
        stack<char> s;
        while (!stacks[j].empty()) {
            s.push(stacks[j].top());
            stacks[j].pop();
        }
        swap(stacks[j], s);
    }

    string s;
    getline(cin, s);
    getline(cin, s);

    while (true) {
        int count, from, to;
        cin >> s >> count >> s >> from >> s >> to;
        if (!cin) break;
/*
        for (int i = 0; i < count; i++) {
            stacks[to-1].push(stacks[from-1].top());
            stacks[from-1].pop();
        }
*/
        stack<char> s;
        for (int i = 0; i < count; i++) {
            s.push(stacks[from-1].top());
            stacks[from-1].pop();
        }
        while (!s.empty()) {
            stacks[to-1].push(s.top());
            s.pop();
        }
    }

    for (int j = 0; j < 9; j++)
        cout << stacks[j].top();
    cout << endl;

    return 0;
}
