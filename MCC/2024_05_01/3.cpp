#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long long
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);
    int ans = 0;
    int cnt = 0;
    int now = A[0];
    for (int i = 0; i < N; i++)
    {
        if (now == A[i])
        {
            cnt++;
        }
        else
        {
            if (cnt < now)
            {
                ans += cnt;
            }
            else
            {
                ans += cnt - now;
            }
            now = A[i];
            cnt = 1;
        }
    }
    if (cnt < now)
    {
        ans += cnt;
    }
    else
    {
        ans += cnt - now;
    }
    cout << ans << endl;
}
