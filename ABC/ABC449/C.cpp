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
    int n, l, r;
    cin >> n >> l >> r;
    string s;
    cin >> s;
    vector<vector<int>> idxs(26);
    for (int i = 0; i < n; i++) {
        idxs[s[i] - 'a'].push_back(i);
    }

    int ans = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < idxs[i].size(); j++) {
            int id = idxs[i][j];
            int left = lower_bound(all(idxs[i]), id + l) - idxs[i].begin();
            int right = lower_bound(all(idxs[i]), id + r + 1) - idxs[i].begin();
            ans += right - left;
        }
    }
    cout << ans << endl;
}
