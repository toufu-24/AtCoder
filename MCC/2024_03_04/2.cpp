#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N, K, X;
    cin >> N >> K >> X;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    RSORT(A);
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        // X円のクーポン
        // 最大で使える枚数
        int ok = 0;
        int ng = K + 1;
        while (ng - ok > 1)
        {
            int mid = (ok + ng) / 2;
            if (A[i] >= X * mid)
            {
                ok = mid;
            }
            else
            {
                ng = mid;
            }
        }
        int can = min(K, ok);
        A[i] -= X * can;
        K -= can;
    }
    RSORT(A);
    for (int i = 0; i < N; i++)
    {
        if (K > 0)
        {
            A[i] = max((ll)0, A[i] - X);
            K--;
        }
    }
    cout << reduce(all(A)) << endl;
}