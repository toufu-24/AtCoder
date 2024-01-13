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
// list<int> ans;
vector<int> ans;
#define TIME_LIMIT 1.95

vector<int> min_cost;
vector<vector<pair<int, int>>> min_path;
vector<pair<pair<int, int>, pair<int, int>>> min_start_end;

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
    return now < TIME_LIMIT;
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

int calc_move_cost(int ax, int ay, int bx, int by)
{
    return abs(ax - bx) + abs(ay - by) + 1;
}

int calc_all_cost(vector<int> &path)
{
    int cost = 0;
    pair<int, int> now = s;
    for (int i = 0; i < path.size(); i++)
    {
        auto [sx, sy] = min_start_end[path[i]].first;
        cost += calc_move_cost(now.first, now.second, sx, sy);
        cost += min_cost[path[i]];
        now = min_start_end[path[i]].second;
    }
    return cost;
}

int main()
{
    time_t start = clock();
    // input
    input();

    // solve
    min_cost.resize(M, 1e9);
    min_path.resize(M);
    min_start_end.resize(M);
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
    for (int i = 0; i < M; i++)
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
        ans.push_back(min_idx);
        now = min_start_end[min_idx].second;
    }

    vector<int> best_ans = ans;
    int best_cost = calc_all_cost(ans);
    int cnt = 0;
    double start_time = clock();
    const double T = TIME_LIMIT - clock() / double(CLOCKS_PER_SEC);
    double startTemp = 0;
    double endTemp = 0;
    while (time_limit(start))
    {
        for (int i = 0; i < ans.size(); i++)
        {
            for (int j = 0; j < ans.size(); j++)
            {
                int prev_cost = calc_all_cost(ans);
                swap(ans[i], ans[j]);
                int next_cost = calc_all_cost(ans);

                double t = (clock() - start_time) / double(CLOCKS_PER_SEC);
                const ll R = 10000;
                double temp = startTemp + (endTemp - startTemp) * t / T;
                double probability = exp((prev_cost - next_cost) / temp);
                bool FORCE_NEXT = probability > (double)(rand() % R) / R;
                if (next_cost > prev_cost && !FORCE_NEXT)
                {
                    swap(ans[i], ans[j]);
                }
                else
                {
                    if (next_cost < best_cost)
                    {
                        best_cost = next_cost;
                        best_ans = ans;
                    }
                }
            }
        }
    }
    // output
    for (auto x : best_ans)
    {
        for (auto y : min_path[x])
        {
            cout << y.first << " " << y.second << '\n';
        }
    }
}