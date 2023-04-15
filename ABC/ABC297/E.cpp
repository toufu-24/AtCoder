#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A);
    // 何個買うかのdp
    ll dp[N + 1][N + 1] = {};
    
}