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
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);

    int Q;
    cin >> Q;
    while (Q--)
    {
        int b;
        cin >> b;
        int idx = lower_bound(all(A), b) - A.begin();

        int ans = 1e18;
        for (int i = -1; i <= 1; i++)
        {
            if (0 <= idx + i && idx + i < N)
            {
                ans = min(ans, abs(A[idx + i] - b));
            }
        }
        cout << ans << endl;
    }
}