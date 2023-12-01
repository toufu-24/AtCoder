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
    int N, D, P;
    cin >> N >> D >> P;
    vector<int> F(N);
    for (int i = 0; i < N; i++)
    {
        cin >> F[i];
    }
    RSORT(F);
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        int sum = 0;
        int j;
        for (j = 0; j < D && i + j < N; j++)
        {
            sum += F[i + j];
        }
        if (sum > P)
        {
            ans += P;
        }
        else
        {
            ans += sum;
        }
        i += D - 1;
    }
    cout << ans << endl;
}