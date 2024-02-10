#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int H, W;
    cin >> H >> W;
    vector<string> C(H);
    for (int i = 0; i < H; i++)
    {
        cin >> C[i];
    }
    vector<vector<int>> dist(H, vector<int>(W, -1));
    dist[0][0] = 1;
    int dx[] = {0, 1};
    int dy[] = {1, 0};
    queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty())
    {
        int nx = q.front().first;
        int ny = q.front().second;
        q.pop();
        for (int i = 0; i < 2; i++)
        {
            int x = nx + dx[i];
            int y = ny + dy[i];
            if (x < 0 || x >= H || y < 0 || y >= W)
            {
                continue;
            }
            if (C[x][y] == '#')
            {
                continue;
            }
            if (dist[x][y] == -1)
            {
                dist[x][y] = dist[nx][ny] + 1;
                q.push({x, y});
            }
        }
    }
    int max_dist = 0;
    for (int i = 0; i < H; i++)
    {
        max_dist = max(max_dist, *max_element(all(dist[i])));
    }
    cout << max_dist;
}