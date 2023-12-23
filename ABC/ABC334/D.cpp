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

int32_t main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> R(N);
    for (int i = 0; i < N; i++)
    {
        cin >> R[i];
    }
    SORT(R);
    vector<int> sum(N + 1);
    for (int i = 0; i < N; i++)
    {
        sum[i + 1] = sum[i] + R[i];
    }

    while (Q--)
    {
        int X;
        cin >> X;
        int idx = upper_bound(all(sum), X) - sum.begin() - 1;
        cout << idx << endl;
    }
}