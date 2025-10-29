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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    map<string, int> mp;
    for (int i = 0; i < n - k + 1; i++) {
        string tmp = s.substr(i, k);
        mp[tmp]++;
    }

    set<string> ans;
    int mx = 0;
    for (auto [t, cnt] : mp) {
        if (cnt > mx) {
            ans.clear();
            ans.insert(t);
        } else if (cnt == mx) {
            ans.insert(t);
        }
        mx = max(mx, cnt);
    }

    cout << mx << endl;
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << endl;
}
