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
    vector<pair<string, int>> SP(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i] >> P[i];
        SP[i] = {S[i], P[i]};
    }
    // 上位 N/2 個の文字列を選ぶ
    sort(SP.begin(), SP.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });
    SP.resize(N / 2);
    S.resize(N / 2);
    P.resize(N / 2);
    for (int i = 0; i < N / 2; i++) {
        S[i] = SP[i].first;
        P[i] = SP[i].second;
    }
    N = N / 2;

    int bestMask = 0;
    int bestScore = 0;
    for (int mask = 0; mask < (1 << N); mask++) {
        vector<int> useIndex;
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                useIndex.push_back(i);
            }
        }
        set<char> useChar;
        for (int i : useIndex) {
            for (auto c : S[i]) {
                useChar.insert(c);
            }
        }
        if (useChar.size() > M)
            continue;

        int score = 0;
        for (int i : useIndex) {
            score += P[i];
        }
        if (score > bestScore) {
            bestScore = score;
            bestMask = mask;
        }
    }
    vector<int> useIndex;
    for (int i = 0; i < N; i++) {
        if (bestMask & (1 << i)) {
            useIndex.push_back(i);
        }
    }
    set<char> useChar;
    for (int i : useIndex) {
        for (auto c : S[i]) {
            useChar.insert(c);
        }
    }
    assert(useChar.size() <= M);
    vector<char> C(M, 'a');
    int idx = 0;
    for (auto c : useChar) {
        C[idx++] = c;
    }
    vector<vector<int>> A(M, vector<int>(M, 0));
    for (int i : useIndex) {
        for (int j = 0; j < S[i].size() - 1; j++) {
            int now_idx = -1, next_idx = -1;
            for (int k = 0; k < M; k++) {
                if (C[k] == S[i][j] && now_idx == -1) {
                    now_idx = k;
                }
                if (C[k] == S[i][j + 1] && next_idx == -1) {
                    next_idx = k;
                }
            }
            // 確率で割り振る
            A[now_idx][next_idx] += 1;
        }
    }
    // 確率を 100 分率に変換
    for (int i = 0; i < M; i++) {
        int sum = 0;
        for (int j = 0; j < M; j++) {
            sum += A[i][j];
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
    // 出力
    for (int i = 0; i < M; i++) {
        cout << C[i];
        for (int j = 0; j < M; j++) {
            cout << ' ' << A[i][j];
        }
        cout << "\n";
    }
}
