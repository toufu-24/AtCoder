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
#define chmax(a, b) = max(a, b)
#define int ll

constexpr int W = 1000;
int D, N;
vector<vector<int>> a;
template <typename T>
void debug(T a)
{
    for (auto e : a)
    {
        for (auto f : e)
        {
            cerr << f;
        }
    }
    cerr << endl;
}

void input()
{
    int _;
    cin >> _ >> D >> N;
    a.resize(D, vector<int>(N));
    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> a[i][j];
        }
    }
}

struct q_data
{
    pair<int, int> end;
    int height;
    int width;
    int area;
};

pair<pair<int, int>, pair<int, int>> empty_space(vector<vector<bool>> &grid, const int area_size)
{
    pair<int, int> empty = {-1, -1};
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (grid[i][j])
            {
                continue;
            }
            pair<int, int> start = {i, j};
            auto compare = [](q_data a, q_data b)
            {
                return a.area < b.area;
            };
            priority_queue<q_data, vector<q_data>, function<bool(q_data, q_data)>> q(compare);
            q.push({{i + 1, j + 1}, 1, 1, 1});
            vector<vector<bool>> visited(W, vector<bool>(W, false));
            visited[i][j] = true;
            auto can_go = [&](pair<int, int> start, pair<int, int> end, bool isTate) -> bool
            {
                if (isTate)
                {
                    for (int y = start.second; y < end.second; y++)
                    {
                        if (grid[end.first][y])
                        {
                            return false;
                        }
                    }
                }
                else
                {
                    for (int x = start.first; x < end.first; x++)
                    {
                        if (grid[x][end.second])
                        {
                            return false;
                        }
                    }
                }
                return true;
            };
            pair<int, int> last;
            while (!q.empty())
            {
                auto [end, height, width, area] = q.top();
                q.pop();
                last = end;
                assert(grid[end.first - 1][end.second - 1] == false);
                if (height * width >= area_size)
                {
                    for (int x = start.first; x < end.first; x++)
                    {
                        for (int y = start.second; y < end.second; y++)
                        {
                            grid[x][y] = true;
                        }
                    }
                    return {start, end};
                }
                if (end.first + 1 <= W && !visited[(end.first + 1) - 1][end.second - 1] && can_go(start, end, true))
                {
                    q.push({{end.first + 1, end.second}, height + 1, width, (height + 1) * width});
                    visited[(end.first + 1) - 1][end.second - 1] = true;
                }
                if (end.second + 1 <= W && !visited[end.first - 1][(end.second + 1) - 1] && can_go(start, end, false))
                {
                    q.push({{end.first, end.second + 1}, height, width + 1, height * (width + 1)});
                    visited[end.first - 1][(end.second + 1) - 1] = true;
                }
            }
            // なかった場合
            cerr << "not found" << endl;
            for (int x = start.first; x < last.first; x++)
            {
                for (int y = start.second; y < last.second; y++)
                {
                    grid[x][y] = true;
                }
            }
            return {start, last};
        }
    }
    assert(false);
    return {empty, {empty.first + 1, empty.second + 1}};
}

int32_t main()
{
    input();
    vector<pair<pair<int, int>, pair<int, int>>> ans;
    for (int i = 0; i < D; i++)
    {
        cerr << i << endl;
        vector<vector<bool>> grid(W, vector<bool>(W, false));
        vector<pair<pair<int, int>, pair<int, int>>> tmp;
        for (int j = N - 1; j >= 0; j--)
        {
            // a[i][j]だけ面積を確保する
            pair<int, int> start, end;
            tie(start, end) = empty_space(grid, a[i][j]);
            tmp.push_back({start, end});
        }
        REVERSE(tmp);
        ans.insert(ans.end(), all(tmp));
    }

    for (auto [start, end] : ans)
    {
        cout << start.first << " " << start.second << " " << end.first << " " << end.second << endl;
    }
}
