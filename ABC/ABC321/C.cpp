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
    if (K < 10)
    {
        cout << K << endl;
        return 0;
    }
    cnt = 9;
    for (int i = 10; true; i++)
    {
        string S = to_string(i);
        bool flag = true;
        for (int j = 0; j < S.size() - 1; j++)
        {
            if (int(S[j] - '0') <= int(S[j + 1] - '0'))
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            cnt++;
            if (cnt == K)
            {
                cout << i << endl;
                return 0;
            }
        }
    }
}