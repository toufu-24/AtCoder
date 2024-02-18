#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    ll A, B, X;
    cin >> A >> B >> X;

    ll left = 0, right = 1e9 + 1;
    while (abs(left - right) > 1)
    {
        ll mid = (left + right) / 2;
        ll cost = A * mid + B * to_string(mid).size();
        if (cost > X)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    cout << left << endl;
}