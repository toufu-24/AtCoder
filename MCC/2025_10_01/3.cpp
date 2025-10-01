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
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    vector<vector<bool>> dp(n + 1, vector<bool>(100 * 100 + 1, false));
    dp[0][0] = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < dp[i].size(); j++) {
            if (dp[i][j]) {
                dp[i + 1][j] = true;
                dp[i + 1][j + s[i]] = true;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < dp[n].size(); i++) {
        if (dp[n][i]) {
            if (i % 10 != 0) {
                ans = i;
            }
        }
    }
    cout << ans << endl;
}