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

vector<string> dfs(vector<string> S, string R, string C, int i, int j) {
    if (i == S.size()) {
        for (int k = 0; k < S.size(); k++) {
            cout << S[k] << endl;
        }
        return S;
    }
    if (j == S[0].size()) {
        S[i][j - 1] = R[i]; // 最も左の文字をRのi文字目に設定
        return dfs(S, R, C, i + 1, 0);
    }
    if (i < S.size() && j < S[0].size()) {
        S[i][j] = R[i]; // Rのi文字目を設定
        auto S1 = dfs(S, R, C, i + 1, 0);
        S[i][j] = C[j]; // Cのj文字目を設定
        auto S2 = dfs(S, R, C, i, j + 1);
        return S1;
    }
    return S;
}

int32_t main() {
    int N;
    cin >> N;
    string R, C;
    cin >> R >> C;
    vector<string> S(N);
    auto ans = dfs(S, R, C, 0, 0);
    for (int i = 0; i < N; i++) {
        cout << ans[i] << endl;
    }
}
