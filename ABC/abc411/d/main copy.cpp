#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main() {
    int n, q;
    cin >> n >> q;
    vector<string> pc(n);
    string server;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int p;
            cin >> p;
            p--;
            pc[p] = server;
        } else if (op == 2) {
            int p;
            string s;
            cin >> p >> s;
            p--;
            pc[p] += s;
        } else if (op == 3) {
            int p;
            cin >> p;
            p--;
            server = pc[p];
        }
    }
    cout << server << endl;
}
