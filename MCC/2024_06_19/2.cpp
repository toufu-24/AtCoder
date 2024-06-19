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
    string S, T;
    cin >> S >> T;
    int ans = 1e18;
    for (int i = 0; i < S.size(); i++)
    {
        if (i + T.size() > S.size())
        {
            break;
        }
        int cnt = 0;
        for (int j = 0; j < T.size(); j++)
        {
            if (S[i + j] != T[j])
            {
                cnt++;
            }
        }
        ans = min(ans, cnt);
    }
    cout << ans << endl;
}
