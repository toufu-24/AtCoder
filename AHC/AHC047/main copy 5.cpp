#include <bits/stdc++.h>
using namespace std;

// ステップ1–4: 文字列選択 → ナップサックDP → Trie構築 (共通接頭辞まとめ) → モデル出力（必ずM個の状態）

struct DPCell {
    double val; // 価値（P_i/|S_i| の合計）
    bool used;  // このセルでアイテム i−1 を使ったか
    int prev_w; // 使っていたら，前の重み j−w_i
    DPCell() : val(0), used(false), prev_w(-1) {}
};

struct TrieNode {
    int next[6];
    bool terminal;
    int id;
    char ch; // このノードに対応する文字
    TrieNode() : terminal(false), id(-1), ch(0) {
        fill(next, next + 6, -1);
    }
};

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

    // ステップ1: 効率 = P_i / |S_i|
    vector<double> efficiency(N);
    for (int i = 0; i < N; i++) {
        efficiency[i] = double(P[i]) / S[i].size();
    }

    // ステップ3: 重み = |S_i|, 価値 = efficiency[i], 容量 = M-1 (ハブ用に1状態確保)
    int W = M - 1;
    vector<vector<DPCell>> dp(N + 1, vector<DPCell>(W + 1));
    for (int i = 1; i <= N; i++) {
        int wi = S[i - 1].size();
        double vi = efficiency[i - 1];
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];
            if (w >= wi) {
                double cand = dp[i - 1][w - wi].val + vi;
                if (cand > dp[i][w].val) {
                    dp[i][w].val = cand;
                    dp[i][w].used = true;
                    dp[i][w].prev_w = w - wi;
                }
            }
        }
    }
    // 復元
    vector<int> chosen;
    int curW = W;
    for (int i = N; i >= 1; i--) {
        if (dp[i][curW].used) {
            chosen.push_back(i - 1);
            curW = dp[i][curW].prev_w;
        }
    }
    reverse(chosen.begin(), chosen.end());

    // ステップ4: Trie 構築 (共通プレフィックスをまとめる)
    vector<TrieNode> trie(1);
    for (int idx : chosen) {
        int u = 0;
        for (char c : S[idx]) {
            int d = c - 'a';
            if (trie[u].next[d] == -1) {
                trie[u].next[d] = trie.size();
                trie.emplace_back();
                trie.back().ch = c;
            }
            u = trie[u].next[d];
        }
        trie[u].terminal = true;
    }

    // ノードに状態IDを割り当て (0: ハブ, 1～: Trieノード)
    trie[0].id = 0;
    int state_cnt = 1;
    for (int i = 1; i < (int)trie.size(); i++) {
        trie[i].id = state_cnt++;
    }

    // 出力用配列をMサイズで初期化
    vector<char> C(M, 'a');
    vector<vector<int>> A(M, vector<int>(M, 0));

    // デフォルト：すべて自己ループ
    for (int i = 0; i < M; i++) {
        A[i][i] = 100;
    }

    // ハブ状態
    C[0] = 'a';
    A[0][0] = 100; // ハブは自己ループ

    // Trieノードの文字割り当てと遷移設定
    for (auto &node : trie) {
        int uid = node.id;
        if (uid == 0)
            continue;
        if (uid >= M)
            break; // M個の状態に収まらないときは無視（通常は state_cnt ≤ M）
        C[uid] = node.ch;
        // 子ノード収集
        vector<int> childs;
        for (int d = 0; d < 6; d++) {
            int nxt = node.next[d];
            if (nxt != -1 && trie[nxt].id < M) {
                childs.push_back(trie[nxt].id);
            }
        }
        if (childs.empty()) {
            // 末端はハブに戻す
            A[uid][0] = 100;
        } else {
            // 均等分配
            int k = childs.size();
            int base = 100 / k, rem = 100 % k;
            for (int i = 0; i < k; i++) {
                A[uid][childs[i]] = base + (i < rem ? 1 : 0);
            }
        }
    }

    // モデル出力: 必ず M 行・M 列
    for (int i = 0; i < M; i++) {
        cout << C[i];
        for (int j = 0; j < M; j++) {
            cout << " " << A[i][j];
        }
        cout << '\n';
    }

    return 0;
}