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
    int n;
    cin >> n;
    map<string, int> mp;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        mp[s[i]]++;
    }
    int m;
    cin >> m;
    vector<string> t(m);
    for (int i = 0; i < m; i++) {
        cin >> t[i];
        mp[t[i]]--;
    }

    int ans = 0;
    for (auto x : mp) {
        ans = max(ans, x.second);
    }
    cout << ans << endl;
}
