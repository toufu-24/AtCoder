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
    int N, K;
    cin >> N >> K;
    vector<int> socks(N, 2);
    vector<int> A(K);
    for (int i = 0; i < K; i++)
    {
        cin >> A[i];
        socks[A[i] - 1]--;
    }
    if (K % 2 == 0)
    {
        int ans = 0;
        for (int i = 0; i < K; i += 2)
        {
            ans += abs(A[i] - A[(i + 1)]);
        }
        cout << ans;
    }
    else
    {
        int ans = 0;
        // どれを消し飛ばすか
        int min_strange = 1e18;
        vector<int> sum(K + 1, 0);
        for (int i = 0; i < K - 1; i += 2)
        {
            sum[i + 1] = sum[i] + abs(A[i] - A[i + 1]);
        }
        vector<int> rsum(K + 1, 0);
        for (int i = K - 1; i > 0; i -= 2)
        {
            rsum[i - 1] = rsum[i] + abs(A[i] - A[i - 1]);
        }
        for (int i = 0; i < K; i++)
        {
            int strange = 0;
            // strange = sum[i - 1] + rsum[i + 1];
            if (i == 0)
            {
                strange = rsum[i + 1];
            }
            else if (i == K - 1)
            {
                strange = sum[i - 1];
            }
            else
            {
                strange = sum[i - 1] + rsum[i + 1];
            }
            min_strange = min(min_strange, strange);
        }
        cout << min_strange;
    }
}