#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

const int64_t mod = 998244353;

int main()
{
    int64_t num[6];
    for (int i = 0; i < 6; i++)
    {
        cin >> num[i];
        if (num[i] >= mod)
        {
            num[i] %= mod;
            if (num[i] < 0)
            {
                num[i] += mod;
            }
        }
    }
    int64_t l_ans = 0;
    l_ans = num[0] * num[1];
    l_ans %= mod;
    if (l_ans < 0)
    {
        l_ans += mod;
    }
    l_ans *= num[2];
    l_ans %= mod;
    if (l_ans < 0)
    {
        l_ans += mod;
    }
    int64_t r_ans = 0;
    r_ans = num[3] * num[4];
    r_ans %= mod;
    if (r_ans < 0)
    {
        r_ans += mod;
    }
    r_ans *= num[5];
    r_ans %= mod;
    if (r_ans < 0)
    {
        r_ans += mod;
    }
    int64_t ans = l_ans - r_ans;
    ans %= mod;
    if (ans < 0)
    {
        ans += mod;
    }
    cout << ans;
}