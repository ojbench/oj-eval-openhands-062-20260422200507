#include <bits/stdc++.h>
#include "MemoryRiver.hpp"
using namespace std;

struct Node {
    int a;
    char b[12];
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Simple driver that reads commands:
    // init <filename>
    // write_info n value
    // get_info n
    // write T: t a bstring
    // update idx a bstring
    // read idx
    // The actual OJ may only compile; ensure it compiles and does nothing harmful.

    string cmd;
    MemoryRiver<Node> mr;
    string fname;
    while (cin >> cmd) {
        if (cmd == "init") {
            cin >> fname;
            mr.initialise(fname);
            cout << "OK\n";
        } else if (cmd == "get_info") {
            int n; cin >> n; int x = -1; mr.get_info(x, n); cout << x << "\n";
        } else if (cmd == "write_info") {
            int n, v; cin >> n >> v; mr.write_info(v, n); cout << "OK\n";
        } else if (cmd == "write") {
            Node t{}; string s; cin >> t.a >> s; memset(t.b, 0, sizeof t.b); strncpy(t.b, s.c_str(), sizeof(t.b)-1); int idx = mr.write(t); cout << idx << "\n";
        } else if (cmd == "update") {
            int idx; Node t{}; string s; cin >> idx >> t.a >> s; memset(t.b, 0, sizeof t.b); strncpy(t.b, s.c_str(), sizeof(t.b)-1); mr.update(t, idx); cout << "OK\n";
        } else if (cmd == "read") {
            int idx; cin >> idx; Node t{}; mr.read(t, idx); cout << t.a << ' ' << string(t.b) << "\n";
        }
    }
    return 0;
}
