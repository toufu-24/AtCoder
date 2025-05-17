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

// https://kmjp.hatenablog.jp/entry/2018/09/28/0900
#define FOR(i, n) for (int i = 0; i < (n); i++)

ll solve() {
    ll N, K;
    ll dp[62][62][2] = {};
    ll num[62][62][2] = {};
    ll mo = 998244353;
    int i, j, k, l, r, x, y;
    string s;

    cin >> N >> K;
    num[0][0][1] = 1;
    FOR(i, 60) {
        FOR(j, 61) {
            ll m = (1LL << (59 - i));

            (dp[i + 1][j][0] += dp[i][j][0]) %= mo;
            (num[i + 1][j][0] += num[i][j][0]) %= mo;

            (dp[i + 1][j + 1][0] += dp[i][j][0] + m % mo * num[i][j][0]) %= mo;
            (num[i + 1][j + 1][0] += num[i][j][0]) %= mo;

            if (N & m) {
                (dp[i + 1][j][0] += dp[i][j][1]) %= mo;
                (num[i + 1][j][0] += num[i][j][1]) %= mo;

                (dp[i + 1][j + 1][1] += dp[i][j][1] + m % mo * num[i][j][1]) %= mo;
                (num[i + 1][j + 1][1] += num[i][j][1]) %= mo;
            } else {
                (dp[i + 1][j][1] += dp[i][j][1]) %= mo;
                (num[i + 1][j][1] += num[i][j][1]) %= mo;
            }
        }
    }

    return (dp[60][K][0] + dp[60][K][1]) % mo;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        cout << solve() << endl;
    }
}
