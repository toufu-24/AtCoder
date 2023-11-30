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

const string snuke = "snuke";

int main()
{
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
    }
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    queue<tuple<int, int, int>> q;
    q.push({0, 0, 0});
    vector visited(H, vector(W, false));
    visited[0][0] = true;
    while (!q.empty())
    {
        int x, y, c;
        tie(x, y, c) = q.front();
        q.pop();
        int nc = (c + 1) % 5;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= H || ny < 0 || ny >= W)
            {
                continue;
            }
            if (visited[nx][ny])
            {
                continue;
            }
            if (S[nx][ny] != snuke[nc])
            {
                continue;
            }
            visited[nx][ny] = true;
            q.push({nx, ny, nc});
        }
    }
    if (visited[H - 1][W - 1])
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}