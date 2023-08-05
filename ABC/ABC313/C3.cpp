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
    if (A.size() == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    // 最大値と最小値の差が1以下になるようにできるか
    ll cnt = 0;
    for (int i = 0; i < N / 2; i++)
    {
        if ((A[i] + A[N - 1 - i]) % 2 == 0)
        {
            A[i] = (A[i] + A[N - 1 - i]) / 2;
            A[N - 1 - i] = A[i];
            cnt += abs(origin_A[i] - A[i]);
        }
        else
        {
            A[i] = (A[i] + A[N - 1 - i]) / 2;
            A[N - 1 - i] = A[i] + 1;
            cnt += abs(origin_A[i] - A[i]);
        }
    }
    sort(A);
    origin_A = A;
    for (int i = 0; i < N / 2; i++)
    {
        if ((A[i] + A[N - 1 - i]) % 2 == 0)
        {
            A[i] = (A[i] + A[N - 1 - i]) / 2;
            A[N - 1 - i] = A[i];
            cnt += abs(origin_A[i] - A[i]);
        }
        else
        {
            A[i] = (A[i] + A[N - 1 - i]) / 2;
            A[N - 1 - i] = A[i] + 1;
            cnt += abs(origin_A[i] - A[i]);
        }
    }

    multiset<ll> s;
    for (ll i = 0; i < N; i++)
    {
        s.insert(A[i]);
    }
    multiset<ll> origin_s = s;
    bool flag = false;
    while (true)
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
        cnt++;
    }
    cout << cnt << endl;
}