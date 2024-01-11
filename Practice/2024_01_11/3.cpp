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
    int N, A, B;
    cin >> N >> A >> B;
    vector<int> X(N);
    for (int i = 0; i < N; i++)
    {
        cin >> X[i];
    }

    int ans = 0;
    for (int i = 0; i < N - 1; i++)
    {
        if (A * (X[i + 1] - X[i]) < B)
        {
            ans += A * (X[i + 1] - X[i]);
        }
        else
        {
            ans += B;
        }
    }
    cout << ans;
}