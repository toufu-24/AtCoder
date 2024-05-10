#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
    }
    // 010101 or 101010 をどっかで切り替え
    vector<int> zero_one(N + 1, 0), one_zero(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        if (i % 2 == 1)
        {
            if (S[i] == '0')
            {
                zero_one[i + 1] = zero_one[i] + C[i];
                one_zero[i + 1] = one_zero[i];
            }
            else
            {
                zero_one[i + 1] = zero_one[i];
                one_zero[i + 1] = one_zero[i] + C[i];
            }
        }
        else
        {
            if (S[i] == '0')
            {
                zero_one[i + 1] = zero_one[i];
                one_zero[i + 1] = one_zero[i] + C[i];
            }
            else
            {
                zero_one[i + 1] = zero_one[i] + C[i];
                one_zero[i + 1] = one_zero[i];
            }
        }
    }
    // 01011 -> 9
    // 10100 -> 15
    int ans = 1e18;
    for (int i = 1; i < N; i++)
    {
        int zero_st = zero_one[i] + one_zero[N] - one_zero[i];
        int one_st = one_zero[i] + zero_one[N] - zero_one[i];
        ans = min({ans, zero_st, one_st});
    }
    cout << ans << endl;
}
