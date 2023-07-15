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
    int N;
    cin >> N;
    string S;
    cin >> S;
    vector<int> zero(N, 0), one(N, 0);
    for (int i = N - 1; i >= 0; i--)
    {
        if (S[i] == '0')
        {
            zero[i]++;
        }
        else
        {
            one[i]++;
        }
        if (i != N - 1)
        {
            zero[i] += zero[i + 1];
            one[i] += one[i + 1];
        }
    }

    ll ans = 0;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == '1')
        {
            ans += zero[i];
        }
        else
        {
            ans += one[i];
        }
    }
    cout << ans << endl;
}