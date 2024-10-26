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
    int N, K;
    cin >> N >> K;

    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
        P[i]--; // 0-indexedに変換
    }

    // ダブリングテーブルのサイズを計算
    int MAX_K = 1;
    while ((1LL << MAX_K) <= K)
        MAX_K++;

    // ダブリングテーブルの初期化
    vector<vector<int>> doubling(MAX_K, vector<int>(N));

    // 1回の操作結果を計算
    for (int i = 0; i < N; i++) {
        doubling[0][i] = P[P[i]];
    }

    // ダブリングテーブルの構築
    for (int k = 0; k + 1 < MAX_K; k++) {
        for (int i = 0; i < N; i++) {
            doubling[k + 1][i] = doubling[k][doubling[k][i]];
        }
    }

    // K回の操作結果を計算
    vector<int> result(N);
    for (int i = 0; i < N; i++)
        result[i] = i;

    for (int k = 0; K > 0; k++) {
        if (K & 1) {
            vector<int> next(N);
            for (int i = 0; i < N; i++) {
                next[i] = doubling[k][result[i]];
            }
            result = next;
        }
        K >>= 1;
    }

    // 結果を出力（1-indexedに戻して出力）
    for (int i = 0; i < N; i++) {
        cout << result[i] + 1 << " \n"[i == N - 1];
    }

    return 0;
}