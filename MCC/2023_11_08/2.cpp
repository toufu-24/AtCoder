#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

map<int, int> memo;

int f(int N)
{
    if (N == 0)
        return memo[0] = 1;
    if (memo.count(N))
        return memo[N];
    if (memo.count(N / 2))
        return memo[N] = memo[N / 2] + f(N / 3);
    if (memo.count(N / 3))
        return memo[N] = f(N / 2) + memo[N / 3];
    return memo[N] = f(N / 2) + f(N / 3);
}

signed main()
{
    ll N;
    cin >> N;
    cout << f(N);
}