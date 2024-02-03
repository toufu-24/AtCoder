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

// セグメントツリーで用いる演算
int op(int a, int b)
{
    return max(a, b);
}

// セグメントツリーの単位元
int e()
{
    return 0;
}

int main()
{
    int N, D;
    cin >> N >> D;

    vector<pair<int, int>> A(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i].first;
        A[i].second = i;
    }
    SORT(A);

    segtree<int, op, e> seg(N);

    for (int i = 0; i < N; ++i)
    {
        int idx = A[i].second;
        int val = A[i].first;
        int l = lower_bound(A.begin(), A.begin() + i + 1, make_pair(val - D, -1)) - A.begin();
        int r = upper_bound(A.begin(), A.begin() + i + 1, make_pair(val + D, INT_MAX)) - A.begin();

        int dp_val = seg.prod(l, r) + 1;
        seg.set(idx, dp_val);
    }

    cout << seg.all_prod() << endl;
}