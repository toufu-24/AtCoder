#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

#define pow(x) ((x) * (x))

int main()
{
    int N;
    cin >> N;
    pair<int, int> start, goal;
    cin >> start.first >> start.second;
    cin >> goal.first >> goal.second;
    vector<tuple<int, int, int>> circles(N);
    for (int i = 0; i < N; i++)
    {
        int x, y, r;
        cin >> x >> y >> r;
        circles[i] = make_tuple(x, y, r);
    }
    int start_idx = 0, goal_idx = 0;
    dsu d(N);
    for (int i = 0; i < N; i++)
    {
        int x1, y1, r1;
        tie(x1, y1, r1) = circles[i];
        for (int j = i + 1; j < N; j++)
        {
            int x2, y2, r2;
            tie(x2, y2, r2) = circles[j];
            int center_dist = pow(x1 - x2) + pow(y1 - y2);
            if (center_dist <= pow(r1 + r2) && /*内部のときをはじく*/ center_dist >= pow(r1 - r2))
            {
                d.merge(i, j);
            }
        }
        if (pow(x1 - start.first) + pow(y1 - start.second) == r1 * r1)
        {
            start_idx = i;
        }
        if (pow(x1 - goal.first) + pow(y1 - goal.second) == r1 * r1)
        {
            goal_idx = i;
        }
    }
    if (d.same(start_idx, goal_idx))
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}