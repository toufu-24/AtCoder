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
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
    }

    int cnt = 0;
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == '#')
            {
                S[i][j] = '.';
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                while (!q.empty())
                {
                    auto [x, y] = q.front();
                    q.pop();
                    for (int d = 0; d < 8; d++)
                    {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (nx < 0 || nx >= H || ny < 0 || ny >= W)
                        {
                            continue;
                        }
                        if (S[nx][ny] == '#')
                        {
                            S[nx][ny] = '.';
                            q.push(make_pair(nx, ny));
                        }
                    }
                }
                cnt++;
            }
        }
    }
    cout << cnt << endl;
}