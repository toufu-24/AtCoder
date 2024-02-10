#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

using mint = modint1000000007;

int main()
{
    int N;
    cin >> N;
    mint ans = 1;
    for (int i = 1; i <= N; i++)
    {
        ans *= i;
    }
    cout << ans.val();
}