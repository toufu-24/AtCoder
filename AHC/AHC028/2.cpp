#pragma GCC optimize("O2")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

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

int N, M;
pair<int, int> s;
vector<vector<char>> keyboard;
vector<string> good_str;
vector<pair<int, int>> ans;

void input()
{
    cin >> N >> M;
    cin >> s.first >> s.second;
    keyboard.resize(N, vector<char>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> keyboard[i][j];
        }
    }
    good_str.resize(M);
    for (int i = 0; i < M; i++)
    {
        cin >> good_str[i];
    }
    SORT(good_str);
}

bool time_limit(time_t start)
{
    double now = double(clock() - start) / CLOCKS_PER_SEC;
    return now < 1.9;
}

bool is_valid(pair<int, int> now)
{
    return 0 <= now.first && now.first < N && 0 <= now.second && now.second < N;
}

pair<int, int> nearest_key(pair<int, int> now, char target, time_t start)
{
    queue<pair<int, int>> q;
    q.push(now);
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    vector visited(N, vector<bool>(N, false));
    visited[now.first][now.second] = true;
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        if (keyboard[x][y] == target)
        {
            return {x, y};
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!is_valid({nx, ny}))
            {
                continue;
            }
            if (visited[nx][ny])
            {
                continue;
            }
            visited[nx][ny] = true;
            q.push({nx, ny});
        }
    }
    return {-1, -1};
}

int main()
{
    time_t start = clock();
    // input
    input();

    // solve
    vector<int> min_cost(M, 1e9);
    vector<vector<pair<int, int>>> min_path(M);
    vector<pair<pair<int, int>, pair<int, int>>> min_start_end(M);
    // それぞれの文字列について、貪欲のパスの最小値を求める
    for (int i = 0; i < M; i++)
    {
        // TODO: ここを高速化する
        string target = good_str[i];
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                if (keyboard[j][k] == target[0])
                {
                    int cost = 0;
                    pair<int, int> now = {j, k};
                    vector<pair<int, int>> path;
                    for (int l = 0; l < target.size(); l++)
                    {
                        auto next = nearest_key(now, target[l], start);
                        cost += abs(now.first - next.first) + abs(now.second - next.second) + 1;
                        path.push_back(next);
                        now = next;
                    }
                    if (cost < min_cost[i])
                    {
                        min_cost[i] = cost;
                        min_path[i] = path;
                        min_start_end[i] = {path[0], path[path.size() - 1]};
                    }
                }
            }
        }
    }

    // 最近傍点で貪欲に結合する
    pair<int, int> now = s;
    vector<int> used(M, false);
    for (int i = 0; i < M && time_limit(start); i++)
    {
        int min_idx = -1;
        int min_cost = 1e9;
        for (int j = 0; j < M; j++)
        {
            if (used[j])
            {
                continue;
            }
            auto [sx, sy] = min_start_end[j].first;
            int cost = abs(now.first - sx) + abs(now.second - sy) + 1;
            if (cost < min_cost)
            {
                min_cost = cost;
                min_idx = j;
            }
        }
        if (min_idx == -1)
        {
            break;
        }
        used[min_idx] = true;
        for (int j = 0; j < min_path[min_idx].size(); j++)
        {
            ans.push_back(min_path[min_idx][j]);
        }
        now = min_start_end[min_idx].second;
    }

    // output
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
}