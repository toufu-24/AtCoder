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

int op_min(int a, int b)
{
    return min(a, b);
}

int e_min()
{
    return 1e18;
}

int op_max(int a, int b)
{
    return max(a, b);
}

int e_max()
{
    return -1e18;
}

int32_t main()
{
    int N, K;
    cin >> N >> K;
    vector<int> P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
    }
    segtree<int, op_min, e_min> seg_min(N + 1);
    segtree<int, op_max, e_max> seg_max(N + 1);
    for (int i = 0; i < N; i++)
    {
        // 値がどこにあるか
        seg_min.set(P[i], i);
        seg_max.set(P[i], i);
    }

    // 最小値aを決め打ち -> [a, a + K)の範囲でのインデックスの最小値と最大値を求める
    int ans = 1e18;
    for (int i = 1; i <= N; i++)
    {
        if (i + K > N + 1)
        {
            break;
        }
        int init_idx = seg_min.prod(i, i + K);
        int last_idx = seg_max.prod(i, i + K);
        ans = min(ans, last_idx - init_idx);
    }

    cout << ans << endl;
}
