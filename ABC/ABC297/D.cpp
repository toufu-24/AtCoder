#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    ll A, B;
    cin >> A >> B;
    ll ans = 0;
    while (true)
    {
        if (A > B)
        {
            swap(A, B);
        }
        if (B % A == 0)
        {
            ans += B / A - 1;
            break;
        }
        ans += B / A;
        B %= A;
    }
    cout << ans << endl;
}