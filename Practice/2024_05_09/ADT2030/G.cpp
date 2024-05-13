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

int op(int a, int b)
{
    return a + b;
}

int e()
{
    return 0;
}

int32_t main()
{
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> plus(N, 0);
    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j < K; j++)
        {
            if (i + j < N)
            {
                plus[i + j] += -A[i];
                A[i + j] += -A[i];
            }
        }
    }

    segtree<int, op, e> seg(plus);
    int Q;
    cin >> Q;
    while (Q--)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int cnt = seg.prod(l, r - 1);
        if (cnt == 0)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}
