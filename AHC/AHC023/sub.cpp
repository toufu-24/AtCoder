#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
// #define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

struct Work
{
    int k, i, j, s;
};

struct crop_struct
{
    int S, D, idx;
};

int T, K, H, W, i0;
vector<crop_struct> crops;
vector<vector<bool>> h, v;
vector<vector<bool>> used;
vector<vector<vector<pair<int, int>>>> graph;
int maxest_dist = 0;

void input()
{
    cin >> T >> H >> W >> i0;
    h.resize(H - 1, vector(W, false));
    for (int i = 0; i < H - 1; ++i)
    {
        string s;
        cin >> s;
        for (int j = 0; j < W; ++j)
        {
            if (s[j] == '1')
                h[i][j] = true;
        }
    }
    v.resize(H, vector(W - 1, false));
    for (int i = 0; i < H; ++i)
    {
        string s;
        cin >> s;
        for (int j = 0; j < W - 1; ++j)
        {
            if (s[j] == '1')
                v[i][j] = true;
        }
    }
    cin >> K;
    crops.resize(K);
    for (int i = 0; i < K; ++i)
    {
        cin >> crops[i].S >> crops[i].D;
        crops[i].idx = i + 1;
    }
    sort(all(crops), [](const crop_struct &a, const crop_struct &b)
         { 
            if (a.D == b.D)
            {
                return a.S < b.S;
            }
            else
            {
                return a.D > b.D;
            } });
    used.resize(H, vector(W, false));

    graph.resize(H, vector(W, vector<pair<int, int>>()));
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            if (i + 1 < H && !h[i][j])
            {
                // no waterway between (i, j) and (i + 1, j)
                graph[i][j].emplace_back(i + 1, j);
                graph[i + 1][j].emplace_back(i, j);
            }
            if (j + 1 < W && !v[i][j])
            {
                // no waterway between (i, j) and (i, j + 1)
                graph[i][j].emplace_back(i, j + 1);
                graph[i][j + 1].emplace_back(i, j);
            }
        }
    }
}

// 出入り口からの距離別に頂点を分類する
auto classify()
{
    queue<pair<int, int>> q;
    q.push({i0, 0});
    vector<vector<int>> dist(H, vector(W, -1));
    dist[i0][0] = 0;
    int max_dist = 0;
    while (!q.empty())
    {
        auto [i, j] = q.front();
        q.pop();
        for (auto [i2, j2] : graph[i][j])
        {
            if (dist[i2][j2] == -1 && !used[i2][j2])
            {
                dist[i2][j2] = dist[i][j] + 1;
                max_dist = max(max_dist, dist[i2][j2]);
                q.push({i2, j2});
            }
        }
    }
    maxest_dist = max(maxest_dist, max_dist);
    vector<vector<pair<int, int>>> res(max_dist + 1);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; ++j)
        {
            if (dist[i][j] != -1)
            {
                res[dist[i][j]].emplace_back(i, j);
            }
        }
    }
    return res;
}

auto max_dist()
{
    queue<pair<int, int>> q;
    q.push({i0, 0});
    vector<vector<int>> dist(H, vector(W, -1));
    dist[i0][0] = 0;
    int max_dist = 0;
    while (!q.empty())
    {
        auto [i, j] = q.front();
        q.pop();
        for (auto [i2, j2] : graph[i][j])
        {
            if (dist[i2][j2] == -1 && !used[i2][j2])
            {
                dist[i2][j2] = dist[i][j] + 1;
                max_dist = max(max_dist, dist[i2][j2]);
                q.push({i2, j2});
            }
        }
    }
    maxest_dist = max(maxest_dist, max_dist);
    vector<pair<int, int>> res;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; ++j)
        {
            if (dist[i][j] == max_dist)
            {
                res.emplace_back(i, j);
            }
        }
    }
    return res;
}

int main()
{
    input();
    max_dist();

    vector<Work> plan;
    int max_D = 0;
    for (int i = 0; i < K; i++)
    {
        max_D = max(max_D, crops[i].D);
    }
    vector<bool> planted(K + 1, false);
    vector<bool> planted_D(max_D + 1, false);
    int now_crop = 0;
    int min_diff_D = 1e9;
    for (int i = 0; i < crops.size(); i++)
    {
        if (min_diff_D > abs(maxest_dist - crops[i].D))
        {
            min_diff_D = abs(maxest_dist - crops[i].D);
            now_crop = i;
        }
    }

    int must_harvest_day = -1;
    int prev_D_k = 1e9;
    for (int k = 0; k < T; k++)
    {
        auto should_plant = max_dist();
        if (should_plant[0] == make_pair(i0, 0))
        {
            continue;
        }
        if (must_harvest_day == -1)
        {
            must_harvest_day = crops[now_crop].D;
        }
        if (must_harvest_day == k || prev_D_k == 1)
        {
            k += must_harvest_day;
            must_harvest_day = -1;
            // T-k以下となるDの作物のidxを取得
            now_crop = 0;
            while (crops[now_crop].D > T - k)
            {
                now_crop++;
            }
            if (now_crop == crops.size())
            {
                now_crop = 0;
            }
            prev_D_k = 1e9;
            planted_D.resize(max_D + 1, false);
            used.resize(H, vector(W, false));
        }
        else
        {
            set<int> planted_set;
            for (int l = 0; l < should_plant.size(); l++)
            {
                int i, j;
                tie(i, j) = should_plant[l];
                if (crops[now_crop].S <= k || planted[now_crop])
                {
                    if (now_crop != crops.size() - 1)
                    {
                        l--;
                        now_crop++;
                    }
                    continue;
                }
                plan.push_back({crops[now_crop].idx, i, j, k});
                planted_set.insert(crops[now_crop].D);
                planted[now_crop] = true;
                used[i][j] = true;
                now_crop++;
            }
            for (auto l : planted_set)
            {
                planted_D[l] = true;
            }
        }
        prev_D_k = crops[now_crop].D - k - 1;
    }
    std::cout << plan.size() << endl;
    for (auto [k, i, j, s] : plan)
    {
        std::cout << k << " " << i << " " << j << " " << s + 1 << endl;
    }
}