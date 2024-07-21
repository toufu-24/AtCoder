#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

constexpr int N = 20;
void input(vector<vector<int>> &h)
{
    int tmp;
    cin >> tmp;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            cin >> h[i][j];
        }
    }
}

bool isAllZero(vector<vector<int>> &h)
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (h[i][j] != 0)
                return false;
        }
    }
    return true;
}

int notZeroCount(vector<vector<int>> &h)
{
    int res = 0;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (h[i][j] != 0)
                res++;
        }
    }
    return res;
}

struct positive_path_ret
{
    vector<vector<int>> res;
    vector<string> ans;
    pair<int, int> car;
    int cost;
    int now_sekisai;
};

positive_path_ret positive_path(vector<vector<int>> &h, vector<pair<int, int>> dir, vector<string> dir_char)
{
    int cost = 0;
    vector<string> ans;
    vector<vector<int>> res = h;
    vector<vector<bool>> used(N, vector<bool>(N, false));
    int now_sekisai = 0;
    pair<int, int> car = {0, 0};
    if (res[0][0] > 0)
    {
        ans.push_back("+" + to_string(res[0][0]));
        now_sekisai += res[0][0];
        cost += res[0][0];
    }
    used[0][0] = true;
    while (true)
    {
        bool flag = false;
        for (int i = 0; i < 4; i++)
        {
            int x = car.first + dir[i].first;
            int y = car.second + dir[i].second;
            if (x < 0 || x >= N || y < 0 || y >= N)
                continue;
            if (used[x][y])
                continue;
            used[x][y] = true;
            car = {x, y};
            ans.push_back(dir_char[i]);
            cost += now_sekisai;
            if (res[x][y] > 0)
            {
                ans.push_back("+" + to_string(res[x][y]));
                now_sekisai += res[x][y];
                res[x][y] = 0;
                cost += res[x][y];
            }
            if (res[x][y] < 0 && now_sekisai >= abs(res[x][y]))
            {
                ans.push_back("-" + to_string(abs(res[x][y])));
                now_sekisai -= abs(res[x][y]);
                res[x][y] = 0;
                cost += abs(res[x][y]);
            }
            flag = true;
            break;
        }
        if (!flag)
            break;
    }
    return {res, ans, car, cost, now_sekisai};
}

int32_t main()
{
    vector<vector<int>> h(N, vector<int>(N));
    input(h);

    pair<int, int> car = {0, 0};
    vector<string> ans;
    int now_sekisai = 0;
    // 0以上のとこからすべてとる
    // 回収
    vector<vector<bool>> used(N, vector<bool>(N, false));
    // 上右左下の優先度をすべてのパターンで試す
    vector<pair<int, int>> dir = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
    vector<string> dir_char = {"U", "R", "L", "D"};
    vector<tuple<int, int, string>> dir_perm;
    for (int i = 0; i < 4; i++)
    {
        dir_perm.push_back({dir[i].first, dir[i].second, dir_char[i]});
    }
    SORT(dir_perm);

    vector<vector<int>> original_h = h;
    vector<string> best_ans;
    int best_cost = 1e18;
    do
    {
        for (int i = 0; i < 4; i++)
        {
            dir[i] = make_pair(get<0>(dir_perm[i]), get<1>(dir_perm[i]));
            dir_char[i] = get<2>(dir_perm[i]);
        }

        auto res = positive_path(original_h, dir, dir_char);
        h = res.res;
        ans = res.ans;
        car = res.car;
        int cost = res.cost;
        now_sekisai = res.now_sekisai;

        // すべてのマスが0以下であるはず
        // 負のマスをめぐる
        vector<pair<int, int>> neg;
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (h[i][j] < 0)
                {
                    neg.push_back({i, j});
                }
            }
        }
        // 貪欲に最短の負のマスを回収
        vector<pair<int, int>> shortest_neg;
        pair<int, int> now = car;
        vector<bool> used_neg(neg.size(), false);
        for (int i = 0; i < neg.size(); i++)
        {
            int shortest_dist = 1e18;
            int shortest_index = -1;
            for (int j = 0; j < neg.size(); j++)
            {
                if (used_neg[j])
                    continue;
                int dist = abs(neg[j].first - now.first) + abs(neg[j].second - now.second);
                if (dist < shortest_dist)
                {
                    shortest_dist = dist;
                    shortest_index = j;
                }
            }
            used_neg[shortest_index] = true;
            now = neg[shortest_index];
            shortest_neg.push_back(neg[shortest_index]);
        }
        for (int i = 0; i < shortest_neg.size(); i++)
        {
            pair<int, int> b = shortest_neg[i];
            if (h[b.first][b.second] == 0)
            {
                continue;
            }

            int dx = b.first - car.first;
            int dy = b.second - car.second;
            if (dx > 0)
            {
                for (int j = 0; j < dx; j++)
                {
                    if (h[car.first][car.second] < 0)
                    {
                        ans.push_back("-" + to_string(abs(h[car.first][car.second])));
                        now_sekisai -= abs(h[car.first][car.second]);
                        h[car.first][car.second] = 0;
                        cost += abs(h[car.first][car.second]);
                    }
                    ans.push_back("D");
                    cost += now_sekisai;
                    car.first++;
                }
            }
            else if (dx < 0)
            {
                for (int j = 0; j < -dx; j++)
                {
                    if (h[car.first][car.second] < 0)
                    {
                        ans.push_back("-" + to_string(abs(h[car.first][car.second])));
                        now_sekisai -= abs(h[car.first][car.second]);
                        h[car.first][car.second] = 0;
                        cost += abs(h[car.first][car.second]);
                    }
                    ans.push_back("U");
                    cost += now_sekisai;
                    car.first--;
                }
            }
            if (dy > 0)
            {
                for (int j = 0; j < dy; j++)
                {
                    if (h[car.first][car.second] < 0)
                    {
                        ans.push_back("-" + to_string(abs(h[car.first][car.second])));
                        now_sekisai -= abs(h[car.first][car.second]);
                        h[car.first][car.second] = 0;
                        cost += abs(h[car.first][car.second]);
                    }
                    ans.push_back("R");
                    cost += now_sekisai;
                    car.second++;
                }
            }
            else if (dy < 0)
            {
                for (int j = 0; j < -dy; j++)
                {
                    if (h[car.first][car.second] < 0)
                    {
                        ans.push_back("-" + to_string(abs(h[car.first][car.second])));
                        now_sekisai -= abs(h[car.first][car.second]);
                        h[car.first][car.second] = 0;
                        cost += abs(h[car.first][car.second]);
                    }
                    ans.push_back("L");
                    cost += now_sekisai;
                    car.second--;
                }
            }
            ans.push_back("-" + to_string(abs(h[b.first][b.second])));
            now_sekisai -= abs(h[b.first][b.second]);
            h[b.first][b.second] = 0;
            cost += abs(h[b.first][b.second]);
        }
        if (cost < best_cost)
        {
            best_cost = cost;
            best_ans = ans;
        }
    } while (next_permutation(all(dir_perm)));
    ans = best_ans;

    for (auto &s : ans)
    {
        cout << s << endl;
    }
}

