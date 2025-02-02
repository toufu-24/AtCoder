#include <bits/stdc++.h>
using namespace std;

#define ll long

int main() {
    ll X, A;
    cin >> X >> A;
    ll N;
    cin >> N;
    vector<ll> L(N), C(N);
    for (ll i = 0; i < N; i++) {
        cin >> L[i] >> C[i];
    }

    // dp[i][l1][l2] := i番目まで見て，レベル1がl1個，レベル2がl2個のときの収穫回数の最大値
    // 合成・収穫は貪欲に行う
    vector<vector<vector<ll>>> dp(N + 1, vector<vector<ll>>(A, vector<ll>(A, -1)));
    dp[0][0][0] = 0;
    for (ll i = 0; i < N; i++) {
        for (ll l1 = 0; l1 < A; l1++) {
            for (ll l2 = 0; l2 < A; l2++) {
                // この状態に遷移できないならスキップ
                if (dp[i][l1][l2] == -1) {
                    continue;
                }
                // 返す場合
                dp[i + 1][l1][l2] = max(dp[i + 1][l1][l2], dp[i][l1][l2]);
                // i番目の作物を収穫する場合
                if (L[i] == 1) {
                    // レベル1
                    ll remain_area = X - l1 - l2;
                    if (remain_area >= C[i]) { // 作物を置ける
                        ll next_l1 = (l1 + C[i]) % A;
                        // レベル2に合成する
                        ll increase_l2 = (l1 + C[i]) / A;
                        ll next_l2 = (l2 + increase_l2) % A;
                        // レベル3に合成する
                        ll increase_l3 = (l2 + increase_l2) / A;
                        dp[i + 1][next_l1][next_l2] = max(dp[i + 1][next_l1][next_l2], dp[i][l1][l2] + increase_l3);
                    }
                } else if (L[i] == 2) {
                    // レベル2
                    ll remain_area = X - l1 - l2;
                    if (remain_area >= C[i]) { // 作物を置ける
                        ll next_l2 = (l2 + C[i]) % A;
                        // レベル3に合成する
                        ll increase_l3 = (l2 + C[i]) / A;
                        dp[i + 1][l1][next_l2] = max(dp[i + 1][l1][next_l2], dp[i][l1][l2] + increase_l3);
                    }
                } else {
                    // レベル3
                    ll remain_area = X - l1 - l2;
                    if (remain_area >= C[i]) { // 作物を置ける
                        dp[i + 1][l1][l2] = max(dp[i + 1][l1][l2], dp[i][l1][l2] + C[i]);
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (ll l1 = 0; l1 < A; l1++) {
        for (ll l2 = 0; l2 < A; l2++) {
            ans = max(ans, dp[N][l1][l2]);
        }
    }
    cout << ans << endl;
}
    