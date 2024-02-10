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
    vector<ll> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<ll> sum(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        sum[i + 1] = sum[i] + A[i];
    }

    map<ll, ll> sum_cnt;
    ll cnt = 0;
    for (int i = 0; i <= N; i++)
    {
        // K = sum[i] - sum[j]
        ll target = sum[i] - K;
        if (sum_cnt.count(target))
        {
            cnt += sum_cnt[target];
        }
        sum_cnt[sum[i]]++;
    }

    cout << cnt;
}
