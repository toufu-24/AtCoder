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

int main()
{
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    pair<int, int> start, goal;
    bool st = false;
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == 'o')
            {
                if (!st)
                {
                    start = make_pair(i, j);
                    st = true;
                }
                else
                {
                    goal = make_pair(i, j);
                }
            }
        }
    }

    queue<pair<int, int>> q;
    q.push(start);
    vector dist(H, vector<int>(W, 1e9));
    dist[start.first][start.second] = 0;
    int dx[4] = {1, 0, -1, 0}, dy[4] = {0, -1, 0, 1};
    while (!q.empty())
    {
        int now_x = q.front().first;
        int now_y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int next_x = now_x + dx[i];
            int next_y = now_y + dy[i];
            if (next_x < 0 || next_x >= H || next_y < 0 || next_y >= W)
            {
                continue;
            }
            if (dist[next_x][next_y] != 1e9)
            {
                continue;
            }
            dist[next_x][next_y] = dist[now_x][now_y] + 1;
            if (next_x == goal.first && next_y == goal.second)
            {
                goto end;
            }
            q.push(make_pair(next_x, next_y));
        }
    }
end:
    cout << dist[goal.first][goal.second];
}