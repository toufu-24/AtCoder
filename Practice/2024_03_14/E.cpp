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
    string ans = "";
    while (N != 0)
    {
        if (N % 2 == 0)
        {
            ans += "B";
            N /= 2;
        }
        else
        {
            ans += "A";
            N--;
        }
    }
    REVERSE(ans);
    cout << ans << endl;
}