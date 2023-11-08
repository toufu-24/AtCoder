// 小さいものが上に来るようにしたいよね
// 排除時に、上にあるものを移動させるけど，その時に移動先を分割する

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

constexpr int MAX_ORDER = 5000;
constexpr int N = 200;
constexpr int M = 10;
constexpr int nDm = 20;
constexpr int padding = -1;
vector<vector<int>> b(M, vector<int>(nDm));
vector<pair<int, int>> ans;

vector<vector<int>> read_input(int n, int m)
{
    vector<vector<int>> b(M, vector<int>(nDm));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < nDm; j++)
        {
            cin >> b[i][j];
        }
    }
    return b;
}

pair<int, int> find_position(int i, const vector<vector<int>> &b)
{
    int x, y;
    for (int j = 0; j < b.size(); j++)
    {
        for (int k = 0; k < b[j].size(); k++)
        {
            if (b[j][k] == i)
            {
                x = j;
                y = k;
                return {x, y};
            }
        }
    }
    return {-1, -1};
}

vector<int> take_above(int x, int y, vector<vector<int>> &b)
{
    vector<int> above;
    for (int j = y + 1; j < b[x].size(); j++)
    {
        above.push_back(b[x][j]);
    }
    for (int j = 0; j < above.size(); j++)
    {
        b[x].pop_back();
    }
    return above;
}

// 移動先を探す
int find_move_index(int x, const vector<vector<int>> &b)
{
    int max = 0;
    int maxIndex = -1;
    for (int j = 0; j < b.size(); j++)
    {
        if (j == x)
            continue;
        ld sum = accumulate(all(b[j]), 0);
        ld ave = 0;
        if (b[j].size() == 0)
        {
            ave = 1e9;
        }
        else
        {
            ave = sum / pow(b[j].size(), 2);
        }
        if (ave > max)
        {
            max = ave;
            maxIndex = j;
        }
    }
    return maxIndex;
}

void solve(int n, int m)
{
    b = read_input(n, m);
    for (int i = 1; i <= n; i++)
    {
        auto [x, y] = find_position(i, b);
        if (y == b[x].size() - 1)
        {
            // 何もしない
        }
        else
        {
            auto above = take_above(x, y, b);
            REVERSE(above);
            vector<int> remove;
            for (auto a : above)
            {
                remove.push_back(a);
                if (a < i + padding)
                {
                    REVERSE(remove);
                    int Index = find_move_index(x, b);
                    for (int j = 0; j < remove.size(); j++)
                    {
                        b[Index].push_back(remove[j]);
                    }
                    // 移動するものを出力
                    ans.push_back({remove[0], Index + 1});
                    remove.clear();
                }
            }
            if (remove.size() != 0)
            {
                REVERSE(remove);
                int Index = find_move_index(x, b);
                for (int j = 0; j < remove.size(); j++)
                {
                    b[Index].push_back(remove[j]);
                }
                // 移動するものを出力
                ans.push_back({remove[0], Index + 1});
            }
        }
        assert(b[x][b[x].size() - 1] == i);
        // 取り出す
        b[x].pop_back();
        // 取り出すものを出力
        ans.push_back({i, 0});
    }
}

int main()
{
    int _n, _m;
    cin >> _n >> _m;
    solve(N, M);
    for (auto [i, j] : ans)
    {
        cout << i << " " << j << endl;
    }
    return 0;
}