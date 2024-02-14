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

int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};

int main()
{
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
    }

    int ans = 0;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] != '#')
            {
                continue;
            }
            ans++;
            S[i][j] = '.';
            queue<pair<int, int>> q;
            q.push({i, j});
            while (!q.empty())
            {
                int x, y;
                tie(x, y) = q.front();
                q.pop();

                for (int k = 0; k < 8; k++)
                {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (nx < 0 || nx >= H || ny < 0 || ny >= W)
                    {
                        continue;
                    }
                    if (S[nx][ny] == '.')
                    {
                        continue;
                    }
                    assert(S[nx][ny] == '#');
                    S[nx][ny] = '.';
                    q.push({nx, ny});
                }
            }
        }
    }
    cout << ans << endl;
}