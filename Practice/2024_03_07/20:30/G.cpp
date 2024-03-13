#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int A, B;
    cin >> A >> B;
    int ans = 0;
    while (A != B)
    {
        if (A > B)
        {
            int cnt = A / B;
            if (A % B == 0)
            {
                cnt--;
            }
            A -= B * cnt;
            ans += cnt;
        }
        else
        {
            int cnt = B / A;
            if (B % A == 0)
            {
                cnt--;
            }
            B -= A * cnt;
            ans += cnt;
        }
    }
    cout << ans << endl;
}