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
    int m, n, N;
    cin >> m >> n >> N;
    int now = N;
    int ans = N;
    int amari = 0;
    while (now >= m)
    {
        amari = now % m;
        now = now / m * n;
        ans += now;
        now += amari;
    }
    cout << ans << endl;
}