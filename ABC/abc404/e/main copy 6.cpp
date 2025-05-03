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
    vector<int> c(n, -1), a(n, 0);
    for (int i = 1; i < n; i++) {
        cin >> c[i];
    }
    int not_zero = 0;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
        if (a[i] != 0) {
            not_zero++;
        }
    }
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= c[i]; j++) {
            int ni = i - j;
            if (ni < 0) {
                break;
            }
            graph[ni].push_back(i);
        }
    }
    assert(graph[n - 1].size() == 0);
    for (int i = 0; i < n; i++) {
        for (auto g : graph[i]) {
            assert(i < g);
        }
    }

    int ans = 1e18;
    vector<vector<int>> dp(n, vector<int>(not_zero + 1, 1e18));
    // dp[i][j]: iまででj個の!0を消すのに必要な最小の遷移回数
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= not_zero; j++) {
            if (dp[i][j] == 1e18) {
                continue;
            }
            for (auto g : graph[i]) {
                if (a[g] == 0) {
                    dp[g][j] = min(dp[g][j], dp[i][j] + 1);
                } else {
                    dp[g][j + 1] = min(dp[g][j + 1], dp[i][j] + 1);
                }
            }
        }
    }
    for (int i = 0; i <= not_zero; i++) {
        ans = min(ans, dp[i][not_zero]);
    }
    cout << ans << endl;
}
