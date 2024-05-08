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
    int A, B, X;
    cin >> A >> B >> X;
    int ans = 0;
    int ok = 0, ng = 1e9 + 1;
    while (abs(ok - ng) > 1)
    {
        int mid = (ok + ng) / 2;
        string tmp = to_string(mid);
        int d = tmp.size();
        if (A * mid + B * d <= X)
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
    }
    cout << ok << endl;
}
