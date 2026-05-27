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
    string s, t;
    cin >> s >> t;

    vector<vector<int>> next(s.size() + 1, vector<int>(26, s.size()));
    for (int i = s.size() - 1; i >= 0; i--) {
        next[i] = next[i + 1];
        next[i][s[i] - 'a'] = i;
    }

    int ans = 0;
    for (int left = 0; left < s.size(); left++) {
        int right = left;
        bool ok = true;
        for (int i = 0; i < t.size(); i++) {
            right = next[right][t[i] - 'a'];
            if (right == s.size()) {
                ok = false;
                break;
            }
            right++;
        }

        if (ok)
            ans += (right - 1) - left;
        else {
            ans += right - left;
        }
    }
    cout << ans << endl;
}
