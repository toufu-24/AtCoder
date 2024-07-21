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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    vector<vector<int>> diff(N, vector<int>(N, -1e18));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            diff[i][j] = A[i] - A[j];
        }
    }
    vector<int> unique_diff;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            unique_diff.push_back(diff[i][j]);
        }
    }
    SORT(unique_diff);
    unique_diff.erase(unique(all(unique_diff)), unique_diff.end());

    // 2個決めればあとは決まるはず...
    // 長さlの単調増加列になるように決める
    // dp[i][l][k] := i番目までみて，長さlで公差がkのものの数
    vector dp(vector(N, vector(N + 1, map<int, mint>())));
    // 初期化
    for (int i = 0; i < N; i++) {
        dp[i][1][0] += 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            dp[i][2][diff[i][j]] += 1;
        }
    }

    // dp遷移
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            for (int l = 3; l <= N; l++) {
                int d = diff[i][j];
                if (dp[j][l - 1].contains(d)) {
                    dp[i][l][d] += dp[j][l - 1][d];
                }
            }
        }
    }

    for (int l = 1; l <= N; l++) {
        mint ans = 0;
        for (int i = 0; i < N; i++) {
            for (auto [k, v] : dp[i][l]) {
                ans += v;
            }
        }
        cout << ans.val() << " ";
    }
    cout << endl;
}
