#include <bits/stdc++.h>
using namespace std;

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
        cin >> A[i];
    sort(A);
    ll ok = pow(10, 9) + 1, ng = -1;
    while (ok - ng > 1)
    {
        ll mid = (ok + ng) / 2;
        ll cnt = 0;
        for (ll i = 0; i < N; i++)
        {
            cnt += mid / A[i];
        }

        if (cnt >= K)
            ok = mid;
        else
            ng = mid;
    }

    cout << ok << endl;
}