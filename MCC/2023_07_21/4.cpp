#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    ll N;
    cin >> N;
    if (N % 2 == 0)
    {
        ll ans = 0;
        ans += N / 10;
        int i = 1;
        while (i < N)
        {
            i *= 5;
            ans += N / i;
        }
        cout << ans;
    }
    else
    {
        cout << 0;
    }
}