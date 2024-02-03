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
    int H, W, N;
    cin >> H >> W >> N;
    vector grid(H, vector(W, '.'));
    vector<pair<int, int>> dxy = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int nx = 0, ny = 0;
    int now_idx = 0;
    for (int i = 0; i < N; i++)
    {
        switch (grid[nx][ny])
        {
        case '.':
            grid[nx][ny] = '#';
            now_idx = (now_idx + 1) % 4;
            nx += dxy[now_idx].first;
            ny += dxy[now_idx].second;
            break;
        case '#':
            grid[nx][ny] = '.';
            now_idx = (now_idx + 3) % 4;
            nx += dxy[now_idx].first;
            ny += dxy[now_idx].second;
            break;
        }
        if (nx < 0)
        {
            nx += H;
        }
        if (nx >= H)
        {
            nx -= H;
        }
        if (ny < 0)
        {
            ny += W;
        }
        if (ny >= W)
        {
            ny -= W;
        }
    }

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }
}