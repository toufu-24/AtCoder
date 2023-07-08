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
    ll N, K;
    cin >> N >> K;
    vector<pair<ll, ll>> A(N);
    ll sum = 0;
    for (ll i = 0; i < N; i++)
    {
        cin >> A[i].first >> A[i].second;
        sum += A[i].second;
    }
    A.push_back({0, 0});
    sort(A);
    for (ll i = 0; i <= N; i++)
    {
        sum -= A[i].second;
        if (sum <= K)
        {
            cout << A[i].first + 1 << endl;
            return 0;
        }
    }
    cout << A[N-1].first + 1 << endl;
}
