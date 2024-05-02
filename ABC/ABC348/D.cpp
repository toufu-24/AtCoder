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

struct medi
{
    int x, y;
    int energy;
};

struct q_data
{
    int x, y;
    int energy;
    map<pair<int, int>, int> medicine;
};

int32_t main()
{
    int H, W;
    cin >> H >> W;
    pair<int, int> start, goal;
    vector<string> S(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == 'S')
            {
                start = {i, j};
            }
            if (S[i][j] == 'T')
            {
                goal = {i, j};
            }
        }
    }
    int N;
    cin >> N;
    vector<medi> M(N);
    map<pair<int, int>, int> mp;
    for (int i = 0; i < N; i++)
    {
        cin >> M[i].x >> M[i].y >> M[i].energy;
        M[i].x--;
        M[i].y--;
        mp[{M[i].x, M[i].y}] = M[i].energy;
    }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    // 到達した際のエネルギーを記録する
    vector<vector<int>> max_energy(H, vector<int>(W, -1e18));
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    max_energy[start.first][start.second] = 0;
    visited[start.first][start.second] = true;
    queue<q_data> q;
    q.push({start.first, start.second, 0, mp});
    while (!q.empty())
    {
        auto [x, y, energy, medicine] = q.front();
        q.pop();
        // 薬を使わない場合
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= H || ny < 0 || ny >= W)
            {
                continue;
            }
            if (S[nx][ny] == '#')
            {
                continue;
            }
            if (visited[nx][ny])
            {
                continue;
            }
            if (energy - 1 <= max_energy[nx][ny])
            {
                continue;
            }
            if (energy <= 0)
            {
                continue;
            }
            q.push({nx, ny, energy - 1, medicine});
            assert(energy - 1 >= max_energy[nx][ny]);
            max_energy[nx][ny] = energy - 1;
            visited[nx][ny] = true;
        }
        // 薬を使う場合
        if (medicine.contains({x, y}))
        {
            energy = medicine[{x, y}];
            medicine.erase({x, y});
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= H || ny < 0 || ny >= W)
                {
                    continue;
                }
                if (S[nx][ny] == '#')
                {
                    continue;
                }
                if (visited[nx][ny])
                {
                    continue;
                }
                if (energy - 1 < max_energy[nx][ny])
                {
                    continue;
                }
                if (energy <= 0)
                {
                    continue;
                }
                q.push({nx, ny, energy - 1, medicine});
                assert(energy - 1 >= max_energy[nx][ny]);
                max_energy[nx][ny] = energy - 1;
                visited[nx][ny] = true;
            }
        }
    }
    if (max_energy[goal.first][goal.second] != -1e18)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}
