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
    // dp[i][j][k] := i番目までの料理で，料理数がj，しょっぱさがkとなるような甘さの最小値
    vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(N + 1, vector<int>(Y + 1, 1e18)));
    dp[0][0][0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            for (int k = 0; k <= Y; k++) {
                if (dp[i][j][k] == 1e18)
                    continue;
                dp[i + 1][j][k] = min(dp[i + 1][j][k], dp[i][j][k]);
                if (j == N) continue;
                if (k + B[i] > Y) continue;
                dp[i + 1][j + 1][k + B[i]] = min(dp[i + 1][j + 1][k + B[i]], dp[i][j][k] + A[i]);
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= N; j++) {
        for (int k = 0; k <= Y; k++) {
            if (dp[N][j][k] <= X) {
                if (j == N) {
                    ans = max(ans, j);
                } else {
                    ans = max(ans, j + 1);
                }
            }
        }
    }
    cout << ans << endl;
}
