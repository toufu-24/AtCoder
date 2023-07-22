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
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
        cin >> S[i];

    queue<pair<int, int>> q;
    int cnt = 1;
    q.push({1, 1});
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<bool>> through(N, vector<bool>(M, false));
    visited[1][1] = true;
    through[1][1] = true;
    while (!q.empty())
    {
        pair<int, int> p = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int next_x = p.first + dx[i];
            int next_y = p.second + dy[i];
            if (S[next_x][next_y] == '#')
            {
                continue;
            }
            if (!through[next_x][next_y])
            {
                cnt++;
            }
            through[next_x][next_y] = true;
            int next_next_x = next_x;
            int next_next_y = next_y;
            while (1)
            {
                next_next_x += dx[i];
                next_next_y += dy[i];
                if (S[next_next_x][next_next_y] == '#')
                {
                    next_next_x -= dx[i];
                    next_next_y -= dy[i];
                    break;
                }
                if (!through[next_next_x][next_next_y])
                {
                    cnt++;
                }
                through[next_next_x][next_next_y] = true;
            }
            if (visited[next_next_x][next_next_y])
            {
                continue;
            }
            q.push({next_next_x, next_next_y});
            visited[next_next_x][next_next_y] = true;
            through[next_next_x][next_next_y] = true;
        }
    }
    cout << cnt << endl;
}