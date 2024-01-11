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

int op(int a, int b)
{
    return a ^ b;
}

int e()
{
    return 0;
}

int32_t main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    segtree<int, op, e> seg(A);

    while (Q--)
    {
        int T, X, Y;
        cin >> T >> X >> Y;
        if (T == 1)
        {
            X--;
            seg.set(X, seg.get(X) ^ Y);
        }
        else
        {
            X--;
            Y--;
            cout << seg.prod(X, Y + 1) << endl;
        }
    }
}