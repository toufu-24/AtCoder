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
    ll N, A, B, C, D, E;
    cin >> N >> A >> B >> C >> D >> E;
    ll neck = min({A, B, C, D, E});
    ll ans = ceil(N / double(neck));
    cout << ans + 4;
}