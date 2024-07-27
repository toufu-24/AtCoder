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
    int N, X, Y;
    cin >> N >> X >> Y;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
    }
    // dp[i][j][k] := i番目までの料理で，甘さがj，しょっぱさがkとなるような最小の料理数
    // vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(X + 1, vector<int>(Y + 1, 1e18)));
    map<int, map<int, int>> dp;
    dp[0][0] = 0;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        vector<tuple<int, int, int>> toAdd;
        for (auto [j, shoppaMap] : dp) {
            if (j > X)
                break;
            for (auto [k, cnt] : shoppaMap) {
                if (k > Y)
                    break;
                if (dp[j].contains(k))
                    dp[j][k] = min(dp[j][k], cnt);
                else
                    dp[j][k] = cnt;

                if (dp[j + A[i]].contains(k + B[i])) {
                    dp[j + A[i]][k + B[i]] = min(dp[j + A[i]][k + B[i]], cnt + 1);
                } else {
                    toAdd.push_back({j + A[i], k + B[i], cnt + 1});
                }
                ans = max(ans, cnt + 1);
            }
        }

        for (auto [j, k, cnt] : toAdd) {
            dp[j][k] = cnt;
        }
    }
    cout << ans << endl;
}
