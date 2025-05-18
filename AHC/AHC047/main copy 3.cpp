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

    // usedで作れるのがあるなら，辺を割り振る
    for (int i = 0; i < N; i++) {
        bool ok = true;
        for (int j = 0; j < S[i].size(); j++) {
            if (!used.contains(S[i][j])) {
                ok = false;
                break;
            }
        }
        if (!ok)
            continue;
        cerr << "new one: " << S[i] << endl;
        for (int j = 0; j < S[i].size() - 1; j++) {
            int now_idx = 0, next_idx = 0;
            for (int k = 0; k < M; k++) {
                if (C[k] == S[i][j]) {
                    now_idx = k;
                }
                if (C[k] == S[i][j + 1]) {
                    next_idx = k;
                }
            }
            // 確率で割り振る
            A[now_idx][next_idx] += 1;
        }
    }

    // Aの行の和が100になるようにする
    for (int i = 0; i < M; i++) {
        int sum = 0;
        for (int j = 0; j < M; j++) {
            sum += A[i][j];
        }
        if (sum == 100) {
            continue;
        }
        int diff = 100 - sum;
        int max_idx = 0;
        for (int j = 1; j < M; j++) {
            if (A[i][j] > A[i][max_idx]) {
                max_idx = j;
            }
        }
        A[i][max_idx] += diff;
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
