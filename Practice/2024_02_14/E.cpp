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

#define pow2(x) (x) * (x)

int32_t main()
{
    int N;
    cin >> N;
    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    dsu d(N + 2);
    vector<int> x(N), y(N), r(N);
    for (int i = 0; i < N; i++)
    {
        cin >> x[i] >> y[i] >> r[i];
    }

    x.push_back(sx);
    y.push_back(sy);
    r.push_back(0);

    x.push_back(tx);
    y.push_back(ty);
    r.push_back(0);

    for (int i = 0; i < N + 2; i++)
    {
        for (int j = i + 1; j < N + 2; j++)
        {
            ll dist = pow2(x[i] - x[j]) + pow2(y[i] - y[j]);
            if (pow2(r[i] - r[j]) <= dist && dist <= pow2(r[i] + r[j]))
            {
                d.merge(i, j);
            }
        }
    }

    if (d.same(N, N + 1))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}