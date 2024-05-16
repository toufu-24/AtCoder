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
    int ans = 0;
    for (int i = 0; i < 1000; i++)
    {
        string t = to_string(i);
        while (t.size() < 3)
        {
            t = '0' + t;
        }
        int idx = 0;
        for (int j = 0; j < N; j++)
        {
            if (S[j] == t[idx])
            {
                idx++;
            }
            if (idx == 3)
            {
                ans++;
                break;
            }
        }
    }
    cout << ans << endl;
}