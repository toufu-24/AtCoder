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

int32_t main() {
    string n;
    cin >> n;

    // 桁DP
    // dp[文字数][Nと一緒か][mod][使用数字]
    vector dp(n.size() + 1, vector(2, vector(3, vector<mint>((1 << 10), 0))));
    dp[0][1][0][0] = 1;
    for (int i = 0; i < n.size(); i++) {
        char c = n[i];
        int cint = c - '0';
        for (int sameN = 0; sameN < 2; sameN++) {
            int lim = sameN ? cint : 9;
            for (int new_d = 0; new_d <= lim; new_d++) {
                for (int mod = 0; mod < 3; mod++) {
                    for (int mask = 0; mask < (1 << 10); mask++) {
                        if (mask == 0 && new_d == 0) {
                            // leading_zeroかつ今回も0
                            dp[i + 1][0][0][0] += dp[i][sameN][mod][mask];
                        } else if (sameN && new_d == lim) {
                            // Nと一緒で今回も一緒になる
                            dp[i + 1][1][(mod * 10 + new_d) % 3][mask | (1 << new_d)] += dp[i][sameN][mod][mask];
                        } else {
                            dp[i + 1][0][(mod * 10 + new_d) % 3][mask | (1 << new_d)] += dp[i][sameN][mod][mask];
                        }
                    }
                }
            }
        }
    }

    mint ans = 0;
    for (int sameN = 0; sameN < 2; sameN++) {
        for (int mod = 0; mod < 3; mod++) {
            for (int mask = 1; mask < (1 << 10); mask++) { // 0だけはダメ
                int one = (mod == 0);
                int two = (((mask >> 3) & 1) == true);
                int three = __builtin_popcount(mask) == 3;
                if (one + two + three == 1) {
                    ans += dp[n.size()][sameN][mod][mask];
                }
            }
        }
    }
    cout << ans.val() << endl;
}
