#pragma GCC optimize("O3")
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
    for (int i = 0; i < M && time_limit(start); i++)
    {
        auto now = s;
        for (int j = 0; j < good_str[i].size(); j++)
        {
            auto next = nearest_key(now, good_str[i][j], start);
            ans.push_back(next);
            now = next;
        }
    }
}
