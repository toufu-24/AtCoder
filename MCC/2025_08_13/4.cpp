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
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    // dp[i][x][y] := i番目をxをした時のyになる個数
    vector dp(n + 1, vector(2, vector<int>(2, 0)));
    dp[0][false][false] = 1;
    dp[0][true][true] = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == "AND") {
            dp[i + 1][true][true] = dp[i][true][true] + dp[i][false][true];
            dp[i + 1][false][true] = 0;
            dp[i + 1][true][false] = dp[i][true][false] + dp[i][false][false];
            dp[i + 1][false][false] = dp[i][true][true] + dp[i][false][true] + dp[i][true][false] + dp[i][false][false];
        } else {
            dp[i + 1][true][true] = dp[i][true][true] + dp[i][false][true] + dp[i][true][false] + dp[i][false][false];
            dp[i + 1][false][true] = dp[i][true][true] + dp[i][false][true];
            dp[i + 1][true][false] = 0;
            dp[i + 1][false][false] = dp[i][true][false] + dp[i][false][false];
        }
    }
    cout << dp[n][true][true] + dp[n][false][true] << endl;
}