#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    ll K;
    cin >> K;
    ll cnt = 0;
    int now_keta = 1;
    while (true)
    {
        string S;
        // 210みたいなのを作る
        for (int i = 0; i < now_keta; i++)
        {
            S += char(now_keta - 1 - i + '0');
        }
        while (true)
        {
            if (S == "0")
            {
                S = "1";
            }
            cnt++;
            if (cnt == K)
            {
                cout << S << endl;
                return 0;
            }

            for (int i = S.size() - 1; i >= 0; i--)
            {
                if (i == 0)
                {
                    // 5210みたいにする
                    if (S[0] == '9')
                    {
                        goto loop;
                    }
                    S = S[0] + 1;
                    for (int j = 1; j < now_keta; j++)
                    {
                        S += char(now_keta - 1 - j + '0');
                    }
                    break;
                }
                if (S[i] < S[i - 1] - 1)
                {
                    S[i]++;
                    break;
                }
            }
        }
    loop:
        now_keta++;
    }
}