#include <bits/stdc++.h>
#include <atcoder/all>
// #include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ull uint64_t

int main()
{
    ull N, X;
    cin >> N >> X;
    string S;
    cin >> S;
    // 何もしないのを'N'とする
    ll prev = N;
    for (ll i = N - 1; i >= 0; i--)
    {
        if (S[i] == 'U')
        {
            for (ll j = min(i, prev) - 1; j >= 0; j--)
            {
                if (S[j] == 'L' || S[j] == 'R')
                {
                    S[j] = 'N';
                    S[i] = 'N';
                    prev = j;
                    break;
                }
            }
        }
    }

    for (ll i = 0; i < N; i++)
    {
        switch (S[i])
        {
        case 'U':
            X = X / 2;
            break;
        case 'L':
            X = 2 * X;
            break;
        case 'R':
            X = 2 * X + 1;
            break;
        default:
            break;
        }
    }
    cout << X << endl;
}