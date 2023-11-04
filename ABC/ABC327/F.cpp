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

signed main()
{
    int N, D, W;
    cin >> N >> D >> W;
    vector<vector<int>> apple(N, vector<int>(2));
    int max_time = 0;
    int max_pos = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> apple[i][0] >> apple[i][1];
        max_time = max(max_time, apple[i][0]);
        max_pos = max(max_pos, apple[i][1]);
    }
    int ans = 0;
    for (int l = 0; l < max_pos; l++)
    {
        int r = l + W;
        for (int t = 0; t < max_time; t++)
        {
            int finish = t + D;
            int cnt = 0;
            for (int i = 0; i < N; i++)
            {
                if (apple[i][0] < finish && apple[i][0] >= t)
                {
                    if (apple[i][1] < r && apple[i][1] >= l)
                    {
                        cnt++;
                    }
                }
            }
            ans = max(ans, cnt);
        }
    }
    cout << ans << endl;
}