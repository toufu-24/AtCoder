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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> x(n), y(n - 1);
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        for (int i = 0; i < n - 1; i++) {
            cin >> y[i];
        }

        // dp[i][j] := i日目に晴れか雨か
        vector<vector<int>> dp(n, vector<int>(2, 0));
        if (s[0] == 'S') {
            dp[0][1] = -x[0];
        } else {
            dp[0][0] = -x[0];
        }
        for (int i = 1; i < n; i++) {
            if (s[i] == 'S') {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + y[i - 1]);
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][0]) - x[i];
            } else {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + y[i - 1]) - x[i];
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][0]);
            }
        }

        cout << max(dp[n - 1][0], dp[n - 1][1]) << endl;
    }
}
