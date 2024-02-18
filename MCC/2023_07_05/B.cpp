#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {

        int W, H, N, D, B;
        cin >> W >> H >> N >> D >> B;
        if (W == 0 && H == 0 && N == 0 && D == 0 && B == 0)
        {
            break;
        }
        vector<pair<int, int>> bomb(N);
        vector<vector<bool>> map(H, vector<bool>(W, false));
        for (int i = 0; i < N; i++)
        {
            cin >> bomb[i].second >> bomb[i].first;
            map[--bomb[i].first][--bomb[i].second] = true;
        }

        queue<pair<int, int>> q;
        q.push(bomb[B - 1]);
        int cnt = 0;
        while (!q.empty())
        {
            int x = q.front().second;
            int y = q.front().first;
            q.pop();
            if (map[y][x])
            {
                cnt++;
                map[y][x] = false;
            }
            else
            {
                continue;
            }
            // x について
            for (int i = -D; i <= D; i++)
            {
                int dx = x + i;
                if (dx < 0 || W <= dx)
                {
                    continue;
                }
                if (map[y][dx])
                {
                    q.push({y, dx});
                }
            }
            // y について
            for (int i = -D; i <= D; i++)
            {
                int dy = y + i;
                if (dy < 0 || H <= dy)
                {
                    continue;
                }
                if (map[dy][x])
                {
                    q.push({dy, x});
                }
            }
            // for (int i = 0; i < H; i++)
            // {
            //     for (int j = 0; j < W; j++)
            //     {
            //         cout << map[i][j];
            //     }
            //     cout << "\n";
            // }
            // cout << "-------------------------------------\n";
        }
        cout << cnt << "\n";
    }
}