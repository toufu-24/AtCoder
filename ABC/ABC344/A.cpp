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

#define int ll

int32_t main()
{
    string S;
    cin >> S;
    int l = 0;
    int r = 0;
    bool flag = false;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == '|')
        {
            if (flag)
            {
                r = i;
            }
            else
            {
                l = i;
                flag = true;
            }
        }
    }
    S.erase(l, r - l + 1);
    cout << S << endl;
}