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

map<pair<int, int>, int> memo;
int combination(int n, int r)
{
    if (r == 0 || r == n)
        return 1;
    else
    {
        if (memo.count({n, r}))
        {
            return memo[{n, r}];
        }
        else
        {
            memo[{n, r}] = combination(n - 1, r - 1) + combination(n - 1, r);
            return memo[{n, r}];
        }
    }
}

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
    vector<int> kind_sum(N + 1, 0);
    for (int i = N - 1; i >= 0; i--)
    {
        kind_sum[i] = kind_sum[i + 1];
        if (i == N - 1 || A[i] != A[i + 1])
        {
            kind_sum[i]++;
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        if (kind_sum[i] >= 3)
        {
            ans += combination(kind_sum[i] - 1, 2);
        }
    }
    cout << ans << endl;
}