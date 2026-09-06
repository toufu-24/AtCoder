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

// #define int ll

int32_t main() {
    int n, q;
    cin >> n >> q;
    // map<int, int> mp, rmp;
    vector<int> mp(n, 0), rmp(n, 0);
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        mp[p[i]] = i;
        rmp[i] = p[i];
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            swap(mp[rmp[x]], mp[rmp[y]]);
            swap(rmp[x], rmp[y]);
        } else {
            // swap(mp, rmp);
            mp.swap(rmp);
        }
    }

    for (auto val : rmp) {
        cout << val + 1 << " ";
    }
}
