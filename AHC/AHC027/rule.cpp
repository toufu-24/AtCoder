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

int N;
vector<string> H, v;
vector<vector<int>> d;
map<pair<int, int>, vector<pair<int, int>>> graph;
vector<vector<bool>> visited;
vector<char> ans;

void input()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    H.resize(N - 1);
    for (int i = 0; i < N - 1; i++)
    {
        cin >> H[i];
    }
    v.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }
    d.resize(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> d[i][j];
        }
    }
    visited.resize(N, vector<bool>(N, false));
}

void make_graph()
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (H[i][j] == '0')
            {
                graph[{i, j}].push_back({i + 1, j});
                graph[{i + 1, j}].push_back({i, j});
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            if (v[i][j] == '0')
            {
                graph[{i, j}].push_back({i, j + 1});
                graph[{i, j + 1}].push_back({i, j});
            }
        }
    }
}
void sort_graph()
{
    for (auto &p : graph)
    {
        sort(all(p.second), [&](pair<int, int> a, pair<int, int> b)
             { return d[a.first][a.second] < d[b.first][b.second]; });
    }
}

char move_char(int x, int y, int nx, int ny)
{
    if (x == nx)
    {
        if (y < ny)
        {
            return 'R';
        }
        else
        {
            return 'L';
        }
    }
    else
    {
        if (x < nx)
        {
            return 'D';
        }
        else
        {
            return 'U';
        }
    }
}

void dfs(int x, int y)
{
    for (auto [nx, ny] : graph[{x, y}])
    {
        if (visited[nx][ny])
        {
            continue;
        }
        ans.push_back(move_char(x, y, nx, ny));
        visited[nx][ny] = true;
        dfs(nx, ny);
        ans.push_back(move_char(nx, ny, x, y));
    }
}

void once()
{
    for (int i = 0; i < N - 1; i++)
    {
        ans.push_back('D');
    }
    for (int j = 0; j < N / 2; j++)
    {
        ans.push_back('R');
        for (int i = 0; i < N - 2; i++)
        {
            ans.push_back('U');
        }
        ans.push_back('R');
        for (int i = 0; i < N - 2; i++)
        {
            ans.push_back('D');
        }
    }
    ans.push_back('U');
    for (int i = 0; i < N - 1; i++)
    {
        ans.push_back('L');
    }
}

void output()
{
    for (auto c : ans)
    {
        cout << c;
    }
}

int main()
{
    input();
    make_graph();
    sort_graph();
    visited[0][0] = true;
    once();
    output();
}