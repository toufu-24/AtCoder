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
    int N, S, M, L;
    cin >> N >> S >> M >> L;
    int ans = 1e18;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < 100; k++)
            {
                if (i * 6 + j * 8 + k * 12 >= N)
                {
                    ans = min(ans, i * S + j * M + k * L);
                }
            }
        }
    }
    cout << ans << endl;
}