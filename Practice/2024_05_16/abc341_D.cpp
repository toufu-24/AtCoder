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
    int N, M, K;
    cin >> N >> M >> K;
    int low = 0, high = 1e18;
    while (high - low > 1)
    {
        int mid = (low + high) / 2;
        int N_div = mid / N;
        int M_div = mid / M;
        int NM_div = mid / lcm(N, M) * 2;
        if (N_div + M_div - NM_div >= K)
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
    }
    cout << high << endl;
}
