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

using mint = modint998244353;

int32_t main()
{
    int N, M;
    cin >> N >> M;

    mint ans = 0;
    for (int i = 0; i < 63; i++)
    {
        int mask = 1LL << i;
        if (M & mask)
        {
            int size = mask << 1;
            int tmp = (N + 1) / size;
            int remain = (N + 1) % size;

            ans += tmp * mask;
            if (remain > mask)
            {
                ans += remain - mask;
            }
        }
    }
    cout << ans.val() << endl;
}
