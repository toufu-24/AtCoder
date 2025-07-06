// Gamble on Ice  —  baseline solver
// g++ -O2 -std=c++17 main.cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M))
        return 0; // N=40 固定
    vector<string> S(N);
    for (int i = 0; i < N; ++i)
        cin >> S[i];

    const int WALL_COL = 20;                // 分断用の縦壁（0-indexed）
    const pair<int, int> ENTRANCE = {0, 0}; // 最後に塞ぐ“入口”マス

    vector<pair<int, int>> order;
    order.reserve(N * N - M);

    auto push_if_free = [&](int x, int y) {
        if (S[x][y] == '.') {
            order.emplace_back(x, y);
            S[x][y] = '#'; // 埋めた扱いにして重複防止
        }
    };

    /* 1. 分断壁を構築（上→下） */
    for (int x = 0; x < N; ++x)
        push_if_free(x, WALL_COL);

    /* 2. その他の空きマスをラフに列挙（ランダムでも可） */
    vector<pair<int, int>> rest;
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
            if (S[x][y] == '.' && make_pair(x, y) != ENTRANCE)
                rest.emplace_back(x, y);
        }
    }
    // ランダムシャッフルで多少事故率を下げる
    mt19937 rng(712687); // 固定シード
    shuffle(rest.begin(), rest.end(), rng);
    order.insert(order.end(), rest.begin(), rest.end());

    /* 3. “入口”を最後に塞ぐ */
    if (S[ENTRANCE.first][ENTRANCE.second] == '.')
        order.push_back(ENTRANCE);

    /* 出力 */
    for (auto [x, y] : order)
        cout << x << ' ' << y << '\n';
    return 0;
}
