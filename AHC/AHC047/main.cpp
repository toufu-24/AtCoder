#include <bits/stdc++.h>
using namespace std;

#define int long

int32_t main() {
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

    // 2. 文字割り当て C[i]：a～f を各 2 つずつ
    vector<char> C(M);
    set<char> used;
    for (int i = 0; i < 6; i++) {
        char ch = 'a' + i;
        C[2 * i] = ch;
        C[2 * i + 1] = ch;
        used.insert(ch);
    }

    // 3. 遷移確率 A[i][j] の初期化：まず 0→1→…→M-1→0 のサイクル
    vector<vector<int>> A(M, vector<int>(M, 0));
    for (int i = 0; i < M - 1; i++) {
        A[i][i + 1] = 0;
    }
    A[M - 1][0] = 0;

    // 4. used で作れる文字列の中から P の大きい順で上位 3 個を選ぶ
    vector<pair<int, int>> cand; // (P, index)
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
    sort(cand.begin(), cand.end(),
         [](auto &a, auto &b) { return a.first > b.first; });
    int K = min(1L, (int)cand.size());

    // 5. 上位 K=3 個の文字列だけに，隣接する文字の状態間に重みを足す
    const int WEIGHT = 200000; // お好みで調整してください
    for (int t = 0; t < K; t++) {
        int idx = cand[t].second;
        // デバッグ出力（不要なら消す）
        cerr << "use string: " << S[idx] << " P=" << P[idx] << "\n";
        const string &str = S[idx];
        for (int j = 0; j + 1 < (int)str.size(); j++) {
            // 文字から状態番号を探す
            int u = -1, v = -1;
            for (int k = 0; k < M; k++) {
                if (C[k] == str[j])
                    u = k;
                if (C[k] == str[j + 1])
                    v = k;
            }
            if (u >= 0 && v >= 0) {
                A[u][v] += WEIGHT;
            }
        }
    }

    // 6. 各行の和を 100 に正規化
    for (int i = 0; i < M; i++) {
        int sum = accumulate(A[i].begin(), A[i].end(), 0);
        if (sum == 0) {
            // 万が一すべて 0 なら 0 に戻る遷移だけ 100%
            A[i][(i + 1) % M] = 100;
            continue;
        }
        // スケールダウン
        for (int j = 0; j < M; j++) {
            A[i][j] = A[i][j] * 100 / sum;
        }
        // 丸め誤差の調整
        int diff = 100 - accumulate(A[i].begin(), A[i].end(), 0);
        if (diff != 0) {
            for (int j = 0; j < M; j++) {
                if (A[i][j] > 0) {
                    A[i][j] += diff;
                    break;
                }
            }
        }
    }

    // 7. 出力
    for (int i = 0; i < M; i++) {
        cout << C[i];
        for (int j = 0; j < M; j++) {
            cout << ' ' << A[i][j];
        }
        cout << "\n";
    }

    return 0;
}
