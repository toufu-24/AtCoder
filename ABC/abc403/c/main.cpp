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
    int n, m, q;
    cin >> n >> m >> q;
    vector<bool> all_watch(n, false);
    vector<set<int>> user(n);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            user[x].insert(y);
        } else if (op == 2) {
            int x;
            cin >> x;
            x--;
            all_watch[x] = true;
        } else {
            int x, y;
            cin >> x >> y;
            x--, y--;
            if (all_watch[x]) {
                cout << "Yes" << endl;
            } else {
                cout << (user[x].contains(y) ? "Yes" : "No") << endl;
            }
        }
    }
}
