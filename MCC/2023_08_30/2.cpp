#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    ll N;
    cin >> N;
    vector<vector<ll>> A(N);
    vector<ll> time(N);
    for (ll i = 0; i < N; i++)
    {
        ll T, K;
        cin >> T >> K;
        time[i] = T;
        A[i].resize(K);
        for (ll j = 0; j < K; j++)
        {
            cin >> A[i][j];
            A[i][j]--;
        }
    }

    vector<bool> already(N, false);
    queue<ll> q;
    q.push(N - 1);
    already[N - 1] = true;
    ll ans = 0;
    while (!q.empty())
    {
        ll now = q.front();
        q.pop();
        ans += time[now];
        for (auto next : A[now])
        {
            if (!already[next])
            {
                q.push(next);
                already[next] = true;
            }
        }
    }
    cout << ans;
}