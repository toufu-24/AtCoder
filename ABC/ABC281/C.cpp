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
    ll N, T;
    cin >> N >> T;
    vector<ll> A(N);
    for (auto &a : A)
    {
        cin >> a;
    }
    ll base = 0;
    for (int i = 0; i < N; i++)
    {
        base += A[i];
    }

    ll sum = 0;
    sum = base * (T / base);
    T = T % base;

    for (int i = 0; i < N; i++)
    {
        sum += A[i];
        if (sum > T)
        {
            cout << i + 1 << " " << T - (sum - A[i]) << endl;
            return 0;
        }
    }
}
