#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
// #define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

constexpr int MAP_SIZE = 20 * 20;

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
vector<bool> planted;
vector<vector<vector<pair<int, int>>>> graph;
set<pair<int, int>> dont_plant;

void input()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
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
    planted.resize(K + 1, false);
    sort(all(crops), [](const crop_struct &a, const crop_struct &b)
         { 
            if (a.D - a.S == b.D - b.S)
            {
                if(a.S == b.S)
                {
                    return a.D < b.D;
                }
                else
                {
                    return a.S < b.S;
                }
            }
            else
            {
                return a.D - a.S > b.D - b.S;
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

auto max_dist2()
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
    vector<pair<int, int>> res;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; ++j)
        {
            if (dist[i][j] == max_dist && !dont_plant.count({i, j}))
            {
                res.emplace_back(i, j);
            }
        }
    }
    return res;
}

int now_plant = 0;
auto now_plant_crops(int need_crops)
{
    vector<crop_struct> res;
    for (int i = now_plant; i < now_plant + need_crops; i++)
    {
        if (i >= crops.size())
        {
            break;
        }
        res.push_back(crops[i]);
    }
    now_plant += need_crops;
    sort(all(res), [](const crop_struct &a, const crop_struct &b)
         { return a.D > b.D; });
    return res;
}

void out(vector<Work> &plan)
{
    std::cout << plan.size() << endl;
    for (auto [k, i, j, s] : plan)
    {
        std::cout << k << " " << i << " " << j << " " << s + 1 << endl;
    }
}

struct harvest_struct
{
    pair<int, int> place;
    int D;
    bool operator<(const harvest_struct &rhs) const
    {
        return D > rhs.D;
    }
};

// 頂点(i0,0)からすべての頂点に到達するために必要なパスの頂点の集合を求める
set<pair<int, int>> findDontPlant()
{
    set<pair<int, int>> res;
    vector<vector<bool>> able_reach(H, vector(W, false));
    queue<pair<int, int>> q;
    q.push({i0, 0});
    able_reach[i0][0] = true;
    while (!q.empty())
    {
        auto [i, j] = q.front();
        q.pop();
        for (auto [i2, j2] : graph[i][j])
        {
            int graph_size = graph[i2][j2].size();
            int able_reach_size = 0;
            for (auto [i3, j3] : graph[i2][j2])
            {
                if (able_reach[i3][j3])
                {
                    able_reach_size++;
                }
            }
            if (able_reach_size != graph_size)
            {
                res.insert({i2, j2});
                for (auto [i3, j3] : graph[i2][j2])
                {
                    able_reach[i3][j3] = true;
                }
                q.push({i2, j2});
            }
        }
    }

    // // セットから削除する要素を記録するためのセット
    // set<pair<int, int>> toRemove;

    // for (auto [i, j] : res)
    // {
    //     int graph_size = graph[i][j].size();
    //     int is_in_set = 0;
    //     for (auto [i2, j2] : graph[i][j])
    //     {
    //         if (res.count({i2, j2}) && !toRemove.count({i2, j2}))
    //         {
    //             is_in_set++;
    //         }
    //         else
    //         {
    //             break;
    //         }
    //     }
    //     if (is_in_set == graph_size)
    //     {
    //         toRemove.insert({i, j});
    //     }
    // }

    // // toRemoveに記録された要素を削除
    // for (const auto &elem : toRemove)
    // {
    //     res.erase(elem);
    // }

    return res;
}

int main()
{
    input();

    // 支配集合を求める
    dont_plant = findDontPlant();
    // // 消せ！！！！------------------------------------
    // cout << dont_plant.size() << endl;
    // int cnt = 0;
    // for (auto [i, j] : dont_plant)
    // {
    //     cout << ++cnt << " " << i << " " << j << " " << 1 << endl;
    // }
    // return 0;
    // //! 消せ！！！！------------------------------------
    vector<Work> plan;
    int how_many_planted = 0;
    priority_queue<harvest_struct> harvest;
    int need_crops = MAP_SIZE;
    vector<pair<int, int>> should_plant_place = max_dist();
    vector<crop_struct> should_plant_crops;
    should_plant_crops = now_plant_crops(need_crops);

    int now_crop_o = 0;
    how_many_planted++;
    while (should_plant_place[0] != make_pair(i0, 0))
    {
        for (int l = 0; l < should_plant_place.size(); l++)
        {
            int i, j;
            tie(i, j) = should_plant_place[l];
            if (should_plant_crops[now_crop_o].S <= 0)
            {
                l--;
                now_crop_o++;
                continue;
            }
            plan.push_back({should_plant_crops[now_crop_o].idx, i, j, 0});
            planted[should_plant_crops[now_crop_o].idx] = true;
            used[i][j] = true;
            harvest.push({{i, j}, should_plant_crops[now_crop_o].D});
            now_crop_o++;
        }

        should_plant_place = max_dist();
    }

    // 日数ごとに処理
    for (int k = 1; k < T; k++)
    {
        should_plant_place = max_dist2();
        while (!harvest.empty() && harvest.top().D == k - 1)
        {
            auto [i, j] = harvest.top().place;
            used[i][j] = false;
            harvest.pop();
        }

        bool once = true;
        // いっぱいまで植える
        while (should_plant_place.size() > 0 && should_plant_place[0] != make_pair(i0, 0))
        {
            int now_crop = 0;
            need_crops = should_plant_place.size();
            should_plant_crops = now_plant_crops(need_crops);
            for (int l = 0; l < should_plant_place.size(); l++)
            {
                int i, j;
                tie(i, j) = should_plant_place[l];
                if (should_plant_crops[now_crop].S <= now_crop)
                {
                    goto end;
                }
                if (should_plant_crops[now_crop].S <= k)
                {
                    l--;
                    now_crop++;
                    continue;
                }
                if (dont_plant.count({i, j}))
                {
                    continue;
                }
                if (now_crop >= should_plant_crops.size())
                {
                    continue;
                }
                plan.push_back({should_plant_crops[now_crop].idx, i, j, k});
                planted[should_plant_crops[now_crop].idx] = true;
                used[i][j] = true;
                harvest.push({{i, j}, should_plant_crops[now_crop].D});
                now_crop++;
            }
            should_plant_place = max_dist2();
        }
    }
end:
    out(plan);
}