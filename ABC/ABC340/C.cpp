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

#define int ll

map<int, int> memo;
int f(int n)
{
    if (n == 1)
        return 0;
    if (memo.count(n))
        return memo[n];
    int lower = floor(double(n) / 2);
    int upper = ceil(double(n) / 2);
    return memo[n] = f(lower) + f(upper) + n;
}

int32_t main()
{
    int N;
    cin >> N;
    cout << f(N) << endl;
}