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
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
    }

    int ans = 1;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == '#')
            {
                continue;
            }
            if (visited[i][j])
            {
                continue;
            }

            queue<pair<int, int>> q;
            q.push({i, j});
            set<pair<int, int>> st;
            st.insert({i, j});
            visited[i][j] = true;
            while (!q.empty())
            {
                auto [x, y] = q.front();
                q.pop();
                bool magnet = false;
                for (int d = 0; d < 4; d++)
                {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if (nx < 0 || nx >= H || ny < 0 || ny >= W)
                    {
                        continue;
                    }
                    if (S[nx][ny] == '#')
                    {
                        magnet = true;
                    }
                }
                if (magnet)
                {
                    continue;
                }
                for (int d = 0; d < 4; d++)
                {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if (nx < 0 || nx >= H || ny < 0 || ny >= W)
                    {
                        continue;
                    }
                    if (st.contains({nx, ny}))
                    {
                        continue;
                    }
                    st.insert({nx, ny});
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
            int cnt = st.size();
            ans = max(ans, cnt);
        }
    }
    cout << ans << endl;
}
