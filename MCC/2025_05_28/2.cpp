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
    int n, m, h, k;
    cin >> n >> m >> h >> k;
    string s;
    cin >> s;
    set<pair<int, int>> items;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        items.insert({x, y});
    }
    int now_x = 0, now_y = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'R') {
            now_x++;
        } else if (s[i] == 'L') {
            now_x--;
        } else if (s[i] == 'U') {
            now_y++;
        } else if (s[i] == 'D') {
            now_y--;
        }
        h--;
        if (h < 0) {
            cout << "No" << endl;
            return 0;
        }
        if (items.count({now_x, now_y})) {
            if (h < k) {
                h = k;
                items.erase({now_x, now_y});
            }
        }
    }
    cout << "Yes" << endl;
}
