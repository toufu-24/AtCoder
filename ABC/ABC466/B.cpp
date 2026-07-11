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
    map<int, int> mp;
    vector<int> c(n), s(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> s[i];
        c[i]--;
        mp[c[i]] = max(mp[c[i]], s[i]);
    }

    for (int i = 0; i < m; i++) {
        if (mp.contains(i))
            cout << mp[i] << endl;
        else
            cout << -1 << endl;
    }
}
