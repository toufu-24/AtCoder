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
    int t;
    cin >> t;
    while (t--)
    {
        vector<int> A(5);
        for (int i = 0; i < 5; i++)
        {
            cin >> A[i];
        }
        vector<int> P(5);
        for (int i = 0; i < 5; i++)
        {
            cin >> P[i];
        }
        // 評価1,2,3は選ぶ価値ない
        int minimum = 1e18;
        auto dfs = [&](auto &&dfs, int ans, int cnt, ld ave) -> void
        {
            if (ave >= 3.0)
            {
                minimum = min(minimum, ans);
                return;
            }
            for (int i = 3; i <= 4; i++)
            {
                ans += P[i];
                ld next_ave = (ave * cnt + (i + 1)) / (cnt + 1);
                dfs(dfs, ans, cnt + 1, next_ave);
                ans -= P[i];
            }
            return;
        };
        ld average = 0;
        for (int i = 0; i < 5; i++)
        {
            average += (i + 1) * A[i];
        }
        average /= reduce(all(A));
        dfs(dfs, 0, reduce(all(A)), average);
        cout << minimum << endl;
    }
}
