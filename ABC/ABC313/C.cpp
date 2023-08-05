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
    ll N;
    cin >> N;
    vector<ll> A(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A);
    vector<ll> origin_A = A;

    ll ok = (*max_element(A.begin(), A.end()) - *min_element(A.begin(), A.end())) * N;
    ll ng = -1;
    while (abs(ok - ng) > 1)
    {
        ll mid = (ok + ng) / 2;
        // 最大値と最小値の差が1以下になるようにできるか
        bool flag = false;
        for (ll i = 0; i < mid; i++)
        {
            ll min_index = min_element(all(A)) - A.begin();
            ll max_index = max_element(all(A)) - A.begin();
            ll min_value = A[min_index];
            ll max_value = A[max_index];
            if (max_value - min_value <= 1)
            {
                flag = true;
                break;
            }
        }
        ll min_val = *min_element(all(A));
        ll max_val = *max_element(all(A));
        if (max_val - min_val <= 1)
        {
            flag = true;
        }
        if (flag)
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
        A = origin_A;
    }
    cout << ok << endl;
}