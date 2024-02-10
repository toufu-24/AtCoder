#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

struct S
{
    ll value;
    int size;
};

struct F
{
    ll add;
};

S op(S a, S b) { return S{a.value + b.value, a.size + b.size}; }

S e() { return S{0, 0}; }

S mapping(F f, S x) { return S{x.value + f.add * x.size, x.size}; }

F composition(F f, F g) { return F{f.add + g.add}; }

F id() { return F{0}; }

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<ll> A(N);
    for (int &a : A)
        cin >> a;
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(N);

    for (int i = 0; i < N; i++)
    {
        seg.set(i, S{A[i], 1});
    }

    for (int i = 0; i < M; i++)
    {
        int B;
        cin >> B;
        ll value = seg.get(B).value;
        seg.set(B, {0, 1});

        // B[i] 以降の要素に +1 を適用
        if (B + value < N)
        {
            seg.apply(B + 1, B + value + 1, F{1});
        }
        else
        {
            seg.apply(B + 1, N, F{1});
            value -= N - B;
            int add = value / N;
            int mod = value % N;
            seg.apply(0, N, F{add});
            seg.apply(0, mod + 1, F{1});
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << seg.get(i).value << " ";
    }
    cout << "\n";
}