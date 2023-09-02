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
    int N, M, P;
    cin >> N >> M >> P;
    int ans = 0;
    int now = M;
    while (now <= N)
    {
        ans++;
        now += P;
    }
    cout << ans;
}
