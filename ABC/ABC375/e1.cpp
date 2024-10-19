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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    int sum_b = reduce(all(b));
    if (sum_b % 3 != 0) {
        cout << -1 << endl;
        return 0;
    }
    // meanに合わせる
    int mean = sum_b / 3;
    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + b[i];
    }
    // dp[i][j][k][l] := i番目までの人で，j,k,lの強さにしたときの移動回数
    // 100 * 500 ^3 ≒ 10^10
    vector<vector<vector<vector<int>>>> dp(n + 1, vector<vector<vector<int>>>(mean + 1, vector<vector<int>>(mean + 1, vector<int>(mean + 1, 1e9))));
    dp[0][0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= mean; j++) {
            for (int k = 0; k <= mean; k++) {
                for (int l = 0; l <= mean; l++) {
                    if (dp[i][j][k][l] == 1e9) {
                        continue;
                    }
                    // a[i]をjにする
                    if (j + b[i] <= mean) {
                        dp[i + 1][j + b[i]][k][l] = min(dp[i + 1][j + b[i]][k][l], dp[i][j][k][l] + (a[i] == 1 ? 0 : 1));
                    }
                    // a[i]をkにする
                    if (k + b[i] <= mean) {
                        dp[i + 1][j][k + b[i]][l] = min(dp[i + 1][j][k + b[i]][l], dp[i][j][k][l] + (a[i] == 2 ? 0 : 1));
                    }
                    // a[i]をlにする
                    if (l + b[i] <= mean) {
                        dp[i + 1][j][k][l + b[i]] = min(dp[i + 1][j][k][l + b[i]], dp[i][j][k][l] + (a[i] == 3 ? 0 : 1));
                    }
                }
            }
        }
    }

    cout << (dp[n][mean][mean][mean] == 1e9 ? -1 : dp[n][mean][mean][mean]) << endl;
}