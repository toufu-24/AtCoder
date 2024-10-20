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
    multiset<ll> s;
    vector<ll> A(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> A[i];
        s.insert(A[i]);
    }
    sort(A);
    vector<ll> origin_A = A;
    multiset<ll> origin_s = s;
    if (A.size() == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    ll ok = 1e11;
    ll ng = -1;
    while (abs(ok - ng) > 1)
    {
        ll mid = (ok + ng) / 2;
        // 最大値と最小値の差が1以下になるようにできるか
        bool flag = false;
        for (ll i = 0; i < mid; i++)
        {
            ll min_value = *begin(s);
            ll max_value = *rbegin(s);
            s.erase(begin(s));
            s.erase(prev(s.end()));

            if (max_value - min_value <= 1)
            {
                flag = true;
                break;
            }
            s.insert(max_value - 1);
            s.insert(min_value + 1);
        }
        ll min_val = *begin(s);
        ll max_val = *rbegin(s);
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
        s = origin_s;
    }
    cout << ok << endl;
}