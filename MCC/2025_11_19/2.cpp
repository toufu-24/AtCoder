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
    map<int, vector<int>> mp;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]].push_back(i + 1);
        // cout << a[i] << ' ' << i + 1 << endl;
    }

    while (q--) {
        int x, k;
        cin >> x >> k;
        if (mp.contains(x) && mp[x].size() >= k)
            cout << mp[x][k - 1]  << endl;
        else
            cout << -1 << endl;
    }
}
