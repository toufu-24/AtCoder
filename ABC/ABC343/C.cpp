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
    int N;
    cin >> N;
    int ans = 0;
    for (int i = 0; i * i * i <= N; i++)
    {
        int tmp = i * i * i;
        string s = to_string(tmp);
        string r = s;
        REVERSE(r);
        if (s == r)
        {
            ans = max(ans, tmp);
        }
    }
    cout << ans << endl;
}