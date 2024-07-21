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
    // 上右左下の優先度
    vector<pair<int, int>> dir = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
    vector<string> dir_char = {"U", "R", "L", "D"};
    if (h[0][0] > 0)
    {
        ans.push_back("+" + to_string(h[0][0]));
        now_sekisai += h[0][0];
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
            if (h[x][y] > 0)
            {
                ans.push_back("+" + to_string(h[x][y]));
                now_sekisai += h[x][y];
                h[x][y] = 0;
            }
            if (h[x][y] < 0 && now_sekisai >= abs(h[x][y]))
            {
                ans.push_back("-" + to_string(abs(h[x][y])));
                now_sekisai -= abs(h[x][y]);
                h[x][y] = 0;
            }
            flag = true;
            break;
        }
        if (!flag)
            break;
    }

    used.assign(N, vector<bool>(N, false));
    // 降ろす
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
            if (h[x][y] < 0)
            {
                ans.push_back("-" + to_string(abs(h[x][y])));
                now_sekisai -= h[x][y];
                h[x][y] = 0;
            }
            flag = true;
            break;
        }
        if (!flag)
            break;
        if (isAllZero(h))
            break;
    }

    for (auto &s : ans)
    {
        cout << s << endl;
    }
}
