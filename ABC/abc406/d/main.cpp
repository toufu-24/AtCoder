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
    int h, w, n;
    cin >> h >> w >> n;
    vector<int> x(n), y(n);
    map<int, set<int>> x_map, y_map;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        x[i]--, y[i]--;
        x_map[x[i]].insert(y[i]);
        y_map[y[i]].insert(x[i]);
    }
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x_q;
            cin >> x_q;
            x_q--;
            int x_val = x_map[x_q].size();
            cout << x_val << endl;
            for (auto x_it : x_map[x_q]) {
                y_map[x_it].erase(x_q);
                if (y_map[x_it].empty()) {
                    y_map.erase(x_it);
                }
            }
            x_map.erase(x_q);
        } else {
            int y_q;
            cin >> y_q;
            y_q--;
            int y_val = y_map[y_q].size();
            cout << y_val << endl;
            for (auto y_it : y_map[y_q]) {
                x_map[y_it].erase(y_q);
                if (x_map[y_it].empty()) {
                    x_map.erase(y_it);
                }
            }
            y_map.erase(y_q);
        }
    }
}
