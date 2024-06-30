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

using mint = modint998244353;

int32_t main()
{
    int N, K;
    cin >> N >> K;
    if (N == 1)
    {
        cout << 1 << endl;
        return 0;
    }
    // 1だけ確率が高い
    // 他は同じ確率
    // 移動する確率が 2(N-1) / N^2
    // そのままいる確率が (N^2 - 2N + 2) / N^2
    // 移動する確率
    const mint move_prob = mint(2 * (N - 1)) / (N * N);
    // そのままいる確率
    const mint stay_prob = mint(mint(N) * N - 2 * N + 2) / (N * N);

    // 黒いボールの位置の期待値
    mint expected_position = 1;
    for (int i = 0; i < K; i++)
    {
        expected_position = expected_position * stay_prob + (((mint(N) * (N + 1)) / 2 - expected_position) / (N - 1)) * move_prob;
    }

    cout << expected_position.val() << endl;
}
