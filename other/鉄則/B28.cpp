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

using mint = modint1000000007;

int main()
{
    int N;
    cin >> N;
    vector<mint> fib(N + 1);
    fib[0] = 0;
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i <= N; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    cout << fib[N].val();
}