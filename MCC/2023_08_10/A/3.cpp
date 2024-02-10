#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    ll N, K, X;
    cin >> N >> K >> X;
    vector<ll> A(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    ll ans = 0;
    ll coupon_cnt = 0;
    bool once = false;
    while (coupon_cnt < K)
    {
        sort(A);
        reverse(A);
        for (ll i = 0; i < N; i++)
        {
            while (A[i] >= X || (once && A[i] > 0))
            {
                if (coupon_cnt >= K)
                {
                    goto end;
                }
                A[i] -= X;
                if (A[i] < 0)
                {
                    A[i] = 0;
                }
                coupon_cnt++;
            }
        }
        if (accumulate(all(A), 0LL) == 0)
        {
            goto end;
        }
        once = true;
    }
end:
    cout << accumulate(all(A), 0LL) << endl;
}