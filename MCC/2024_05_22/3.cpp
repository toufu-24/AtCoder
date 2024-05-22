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
    vector<int> x(N), y(N);
    vector<pair<int, int>> xy(N);
    map<int, vector<int>> x_point;
    map<int, set<int>> y_point;
    for (int i = 0; i < N; i++)
    {
        cin >> x[i] >> y[i];
        xy[i] = {x[i], y[i]};
    }
    SORT(xy);

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        auto same_x = x_point[x[i]];
        int origin_y = y[i];
        for (auto next_y : same_x)
        {
            if (next_y == origin_y)
                continue;
            for (auto next_x : y_point[next_y])
            {
                // {next_x, origin_y}が存在するか
                if (y_point[origin_y].contains(next_x))
                    ans++;
            }
        }
        x_point[x[i]].push_back(y[i]);
        y_point[y[i]].insert(x[i]);
    }
    cout << ans << endl;
}