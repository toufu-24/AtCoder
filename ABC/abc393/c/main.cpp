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
    int n, m;
    cin >> n >> m;
    int ans = 0;
    set<pair<int, int>> s;
    for (int i = 0; i < n; i++) {
        s.insert({i, i});
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v)
            swap(u, v);
        if (s.count({u, v})) {
            ans++;
        }
        s.insert({u, v});
    }
    cout << ans << endl;
}
