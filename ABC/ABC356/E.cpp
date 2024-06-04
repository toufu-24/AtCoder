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

// 和を保持するモノイドの構造体
struct S
{
    int sum;  // その区間の総和
    int size; // 区間のサイズ
};

// 作用としての積を定義
using F = ld;

// 和を保持するモノイドの二項演算
S op(S a, S b)
{
    return {a.sum + b.sum, a.size + b.size};
}

// 作用を区間にマッピング
S mapping(F f, S x)
{
    if (f == 1)
        return x;               // 単位元のときは変更を加えない
    return {x.sum / f, x.size}; // 区間の和を更新
}

// 作用の合成
F composition(F f, F g)
{
    return f * g;
}

// モノイドの単位元
S e() { return {0, 0}; }

// 作用の単位元
F id() { return 1; }

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);

    lazy_segtree<S, op, e, F, mapping, composition, id> seg(N);
    for (int i = 0; i < N; i++)
    {
        seg.set(i, {A[i], 1});
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        // 右側に対して / A[i] する
        seg.apply(i + 1, N, 1.0 / A[i]);

        int sum = seg.prod(i + 1, N).sum;
        ans += sum;

        // 元に戻す
        seg.apply(i + 1, N, A[i]);
    }
    cout << ans << endl;
}