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
    int N, M;
    cin >> N >> M;
    vector<int> a(M);
    vector<vector<int>> c(M);
    vector<int> c_bit(M, 0);
    for (int i = 0; i < M; i++) {
        int _a, b;
        cin >> _a >> b;
        a[i] = _a;
        c[i].resize(b);
        for (int j = 0; j < b; j++) {
            cin >> c[i][j];
            c[i][j]--;
        }

        for (int j = 0; j < b; j++) {
            c_bit[i] |= (1 << c[i][j]);
        }
    }

    // dp[i][j] := i番目までの鍵を見た時に，空けられる集合の状態がjであるような最小値
    vector<vector<int>> dp(M + 1, vector<int>(1 << N, 1e18));
    dp[0][0] = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < (1 << N); j++) {
            dp[i + 1][j] = dp[i][j];
        }
        for (int j = 0; j < (1 << N); j++) {
            dp[i + 1][j | c_bit[i]] = min(dp[i + 1][j | c_bit[i]], dp[i][j] + a[i]);
        }
    }

    if (dp[M][(1 << N) - 1] == 1e18) {
        cout << -1 << endl;
    } else {
        cout << dp[M][(1 << N) - 1] << endl;
    }
}
