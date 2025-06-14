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

bool chmax(int &a, int b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

int32_t main() {
    int n, h, m;
    cin >> n >> h >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    // dp[i][j] := i番目の敵が終わったとき、体力がjのときの魔力
    vector<map<int, int>> dp(n + 1);
    dp[0][h] = m;
    for (int i = 0; i < n; i++) {
        for (auto [tairyoku, maryoku] : dp[i]) {
            if (tairyoku >= a[i]) {
                chmax(dp[i + 1][tairyoku - a[i]], maryoku);
            }
            if (maryoku >= b[i]) {
                chmax(dp[i + 1][tairyoku], maryoku - b[i]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        if (dp[i].size() != 0) {
            ans = i;
        }
    }

    cout << ans << endl;
}
