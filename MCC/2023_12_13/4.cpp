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
int N;
vector<int> A;

int calc_score(int b)
{
    int res = 0;
    for (int i = 0; i < N; i++)
    {
        res += abs(A[i] - (b + i + 1));
    }
    return res;
}

int32_t main()
{
    cin >> N;
    A.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    int low = -1e9, high = 1e9 + 10;
    while (high - low > 2)
    {
        int c1 = (low * 2 + high) / 3;
        int c2 = (low + high * 2) / 3;
        if (calc_score(c1) > calc_score(c2))
        {
            low = c1;
        }
        else
        {
            high = c2;
        }
    }
    int ans = 1e18;
    for (int i = low; i <= high; i++)
    {
        ans = min(ans, calc_score(i));
    }
    cout << ans;
}