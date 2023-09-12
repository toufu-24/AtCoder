
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

int main()
{
    ll N;
    cin >> N;
    ll ans = 0;
    ans += N / 3;
    ans += N / 5;
    ans += N / 7;
    ans -= N / 15;
    ans -= N / 21;
    ans -= N / 35;
    ans += N / (3 * 5 * 7);
    cout << ans;
}
