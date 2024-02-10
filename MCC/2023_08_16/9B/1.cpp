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
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
    }
    sort(C);
    for (int i = 0; i < N; i++)
    {
        ans *= C[i] - i;
    }
    cout << ans.val();
}