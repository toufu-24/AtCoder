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

using mint = modint998244353;

int32_t main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> indexes(11);
    for (int i = 0; i < n; i++) {
        indexes[s[i] - '0'].push_back(i);
    }

    mint ans = 0;
    for (int i = 0; i < n; i++) {
    }

    cout << ans.val() << endl;
}
