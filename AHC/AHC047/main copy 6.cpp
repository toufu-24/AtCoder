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

    // 1) usedで作れる文字列を集める
    vector<pair<int, int>> cand; // (P[i], i)
    for (int i = 0; i < N; i++) {
        bool ok = true;
        for (char ch : S[i]) {
            if (!used.count(ch)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cand.emplace_back(P[i], i);
        }
    }
    // 2) P の大きい順にソートして最大２つまで
    sort(cand.begin(), cand.end(),
         [](auto &a, auto &b) { return a.first > b.first; });
    int K = min(4, (int)cand.size());
    // 3) 上位K個についてだけ遷移を割り振る
    for (int t = 0; t < K; t++) {
        int i = cand[t].second;
        // デバッグ出力（必要なければ消してください）
        cerr << "use string: " << S[i] << " P=" << P[i] << endl;
        for (int j = 0; j + 1 < (int)S[i].size(); j++) {
            // 文字から状態番号を探す
            int now_idx = -1, next_idx = -1;
            for (int k = 0; k < M; k++) {
                if (C[k] == S[i][j])
                    now_idx = k;
                if (C[k] == S[i][j + 1])
                    next_idx = k;
            }
            // 見つかったなら確率を上乗せ
            if (now_idx >= 0 && next_idx >= 0) {
                A[now_idx][next_idx] += 150;
            }
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
        if (sum == 0) {
            A[i][0] = 100;
            continue;
        }
        for (int j = 0; j < M; j++) {
            A[i][j] = A[i][j] * 100 / sum;
        }
        // ちゃんと 100 になるように調整
        int diff = 100 - accumulate(A[i].begin(), A[i].end(), 0);
        if (diff > 0) {
            for (int j = 0; j < M; j++) {
                if (A[i][j] > 0) {
                    A[i][j] += diff;
                    break;
                }
            }
        } else if (diff < 0) {
            for (int j = 0; j < M; j++) {
                if (A[i][j] > 0) {
                    A[i][j] += diff;
                    break;
                }
            }
        }
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
