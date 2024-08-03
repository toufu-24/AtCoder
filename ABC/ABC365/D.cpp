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
    int N;
    cin >> N;
    string S;
    cin >> S;
    // dp[i][j] := i手目に、j番目の手を出した時の最大の得点
    // R P S
    vector<vector<int>> dp(N + 1, vector<int>(3, 0));
    if (S[0] == 'R') {
        dp[1][0] = 0;
        dp[1][1] = 1;
        dp[1][2] = 0;
    }
    if (S[0] == 'P') {
        dp[1][0] = 0;
        dp[1][1] = 0;
        dp[1][2] = 1;
    }
    if (S[0] == 'S') {
        dp[1][0] = 1;
        dp[1][1] = 0;
        dp[1][2] = 0;
    }
    for (int i = 1; i < N; i++) {
        // R -> グー なので Pで勝ってRであいこ
        if (S[i] == 'R') {
            dp[i + 1][0] = max(dp[i][1], dp[i][2]); // あいこ
            dp[i + 1][1] = max(dp[i][0] + 1, dp[i][2] + 1); // 勝ち
            // dp[i + 1][2] = max(dp[i][0], dp[i][1]); // 負け
        }
        // P -> パー なので Sで勝ってPであいこ
        else if (S[i] == 'P') {
            // dp[i + 1][0] = max(dp[i][1], dp[i][2]);
            dp[i + 1][1] = max(dp[i][0], dp[i][2]);
            dp[i + 1][2] = max(dp[i][0] + 1, dp[i][1] + 1);
        }
        // S -> チョキ なので Rで勝ってSであいこ
        else {
            dp[i + 1][0] = max(dp[i][1] + 1, dp[i][2] + 1);
            // dp[i + 1][1] = max(dp[i][0], dp[i][2]);
            dp[i + 1][2] = max(dp[i][0], dp[i][1]);
        }
    }

    int ans = 0;
    for (int i = 0; i < 3; i++) {
        ans = max(ans, dp[N][i]);
    }
    cout << ans << endl;
}