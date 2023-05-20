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
    ll N, M, D;
    cin >> N >> M >> D;
    vector<ll> A(N);
    vector<ll> B(M);
    for (ll i = 0; i < N; i++)
        cin >> A[i];
    for (ll i = 0; i < M; i++)
        cin >> B[i];
    sort(A);
    sort(B);
    // 二分探索
    bool ans = false;
    ll maximam = 0;
    for (int i = 0; i < N; i++)
    {
        ll ok = -1;
        ll ng = M;
        while (abs(ok - ng) > 1)
        {
            ll mid = (ok + ng) / 2;
            if (abs(B[mid] - A[i]) <= D)
                ok = mid;
            else
                ng = mid;
        }
        if (ok != -1)
        {
            ans = true;
            maximam = max(maximam, A[i] + B[ok]);
        }
    }
    for (int i = 0; i < M; i++)
    {
        ll ok = -1;
        ll ng = N;
        while (abs(ok - ng) > 1)
        {
            ll mid = (ok + ng) / 2;
            if (abs(B[i] - A[mid]) <= D)
                ok = mid;
            else
                ng = mid;
        }
        if (ok != -1)
        {
            ans = true;
            maximam = max(maximam, A[ok] + B[i]);
        }
    }
    if (ans)
        cout << maximam;
    else
        cout << -1;
}
