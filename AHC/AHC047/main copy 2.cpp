#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    long long L;
    cin >> N >> M >> L;

    vector<string> S(N);
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i] >> P[i];
    }

    // 1. P が最大のインデックスを探す
    int t = 0;
    for (int i = 1; i < N; i++) {
        if (P[i] > P[t]) {
            t = i;
        }
    }
    string best = S[t];
    int len = best.size();

    // 2. 文字割り当て C[i]
    set<char> used;
    vector<char> C(M, 'a');
    for (int i = 0; i < len; i++) {
        C[i] = best[i];
        used.insert(best[i]);
    }
    // 残りは 'a' のまま

    // 3. 遷移確率 A[i][j]
    vector<vector<int>> A(M, vector<int>(M, 0));
    // 0→1→2→...→len-1→0 のサイクル
    for (int i = 0; i < len - 1; i++) {
        A[i][i + 1] = 100;
    }
    if (len > 0) {
        A[len - 1][0] = 100;
    }
    // 残りの状態は全部 0 に戻す
    for (int i = len; i < M; i++) {
        A[i][0] = 100;
    }

    // 4. 出力
    for (int i = 0; i < M; i++) {
        // 文字
        cout << C[i];
        // 100 分率での確率
        for (int j = 0; j < M; j++) {
            cout << ' ' << A[i][j];
        }
        cout << "\n";
    }

    return 0;
}
