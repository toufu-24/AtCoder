#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

signed main()
{
    int N, P, Q, R;
    cin >> N >> P >> Q >> R;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> sum(N + 1);
    sum[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        sum[i] = sum[i - 1] + A[i - 1];
    }

    for (int x = 0; x < N; x++)
    {
        // P
        int y = lower_bound(all(sum), P + sum[x]) - sum.begin();
        if (y == N + 1 || sum[y] - sum[x] != P)
        {
            continue;
        }
        assert(x < y);
        // Q
        int z = lower_bound(all(sum), Q + sum[y]) - sum.begin();
        if (z == N + 1 || sum[z] - sum[y] != Q)
        {
            continue;
        }
        assert(y < z);
        // R
        int w = lower_bound(all(sum), R + sum[z]) - sum.begin();
        if (w == N + 1 || sum[w] - sum[z] != R)
        {
            continue;
        }
        assert(z < w);
        cout << "Yes" << endl;
        cerr << x << " " << y << " " << z << " " << w << endl;
        return 0;
    }
    cout << "No";
}