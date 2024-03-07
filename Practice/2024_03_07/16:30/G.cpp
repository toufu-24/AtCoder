#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

using S = ll;
using F = ll;

const S INF = 8e18;

S op(S a, S b) { return std::min(a, b); }
S e() { return INF; }
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<int> X(M);
    for (int i = 0; i < M; i++)
    {
        cin >> X[i];
        X[i]--;
    }
    vector<int> s(N, 0);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(s);
    int init = 0;
    for (int i = 0; i < M - 1; i++)
    {
        init += min(abs(X[i] - X[i + 1]), N - abs(X[i] - X[i + 1]));
        int l = min(X[i], X[i + 1]);
        int r = max(X[i], X[i + 1]);
        if (r - l < N - (r - l))
        {
            seg.apply(l, r, 1);
        }
        else
        {
            seg.apply(r, N, 1);
            seg.apply(0, l, 1);
        }
    }
    cerr << init << endl;
    int del = seg.all_prod();

    int ans = 0;
    for (int i = 0; i < M - 1; i++)
    {
        int l = min(X[i], X[i + 1]);
        int r = max(X[i], X[i + 1]);
        if (l <= del && del < r)
        {
            ans += N - (r - l);
        }
        else
        {
            ans += r - l;
        }
    }
    cout << ans << endl;
}