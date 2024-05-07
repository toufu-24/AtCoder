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
    int ans = 1e9;
    for (int i = 0; i < S.size(); i++)
    {
        int num = 0;
        string tmp = S.substr(i, 3);
        num = stoi(tmp);
        ans = min(ans, abs(753 - num));
    }
    cout << ans << endl;
}
