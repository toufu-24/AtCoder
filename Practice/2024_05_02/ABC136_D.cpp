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
    string S;
    cin >> S;
    int r = 0;
    int l = 0;
    vector<int> ans(S.size(), 0);
    bool left = false;
    int idx = 0;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == 'R')
        {
            if (left)
            {
                ans[idx - 1] = (r + 1) / 2 + l / 2;
                ans[idx] = r / 2 + (l + 1) / 2;
                r = 0;
                l = 0;
            }
            r++;
            left = false;
        }
        else
        {
            if (!left)
            {
                idx = i;
            }
            l++;
            left = true;
        }
    }
    ans[idx - 1] = (r + 1) / 2 + l / 2;
    ans[idx] = r / 2 + (l + 1) / 2;

    for (int i = 0; i < S.size(); i++)
    {
        cout << ans[i] << " ";
    }
}
