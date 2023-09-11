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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> dp(N, 1e9);
    for (int i = 0; i < N; i++)
    {
        int idx = lower_bound(all(dp), A[i]) - dp.begin();
        dp[idx] = A[i];
    }
    cout << lower_bound(all(dp), 1e9) - dp.begin() << endl;
}