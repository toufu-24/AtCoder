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
#define chmax(a, b) a = max(a, b)
#define int ll

constexpr int W = 1000;
int D, N;
vector<vector<int>> a;
const vector<int> thousand_divisor = {1, 2, 5, 10, 20, 25, 50, 100, 125, 250, 500, 1000};

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

struct seat_data
{
    pair<int, int> left_up;
    pair<int, int> right_down;
};

// 広げることができるかどうか
bool can_put(const pair<int, int> &left_up, const pair<int, int> &right_down, int idx, const vector<vector<int>> &grid, bool isFirst)
{
    // 座席の範囲がボードの外側にはみ出ていないかチェック
    if (right_down.first > W || right_down.second > W)
    {
        return false;
    }
    if (left_up.first < 0 || left_up.second < 0)
    {
        return false;
    }
    // 他の座席と重なっていないかチェック
    if (isFirst)
    {
        for (int i = left_up.second; i < right_down.second; i++)
        {
            if (grid[right_down.first - 1][i] == -1 || grid[right_down.first - 1][i] == idx)
            {
                return false;
            }
        }
    }
    else
    {
        for (int i = left_up.first; i < right_down.first; i++)
        {
            if (grid[i][right_down.second - 1] == -1 || grid[i][right_down.second - 1] == idx)
            {
                return false;
            }
        }
    }

    return true;
}

int32_t main()
{
    // 探索すべき対象 : 長方形の形・位置
    input();
    int start_area = W * W / (N);
    int start_side = sqrtl(start_area);
    start_side = *prev(lower_bound(all(thousand_divisor), start_side));
    int thousand_idx = lower_bound(all(thousand_divisor), start_side) - thousand_divisor.begin();
    vector<vector<int>> grid(W, vector<int>(W, -1));
    vector<string> debug_grid(W, string(W, '.'));
    vector<int> biggest(N, 0);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < D; j++)
        {
            chmax(biggest[i], a[j][i]);
        }
    }
    // biggest[i]が収まる面積の長方形のしきつめを考える
    // まず，start_sideを1辺とする正方形を配置する
    vector<seat_data> seat;
    pair<int, int> left_up = {0, 0};
    pair<int, int> right_down = {start_side, start_side};
    for (int i = 0; i < N; i++)
    {
        for (int w = left_up.first; w < right_down.first; w++)
        {
            for (int h = left_up.second; h < right_down.second; h++)
            {
                grid[w][h] = i;
                debug_grid[w][h] = '0' + i;
            }
        }
        seat.push_back({left_up, right_down});
        left_up.first += start_side;
        right_down.first += start_side;
        if (right_down.first > W)
        {
            left_up.first = 0;
            right_down.first = start_side;
            left_up.second += start_side;
            right_down.second += start_side;
        }
    }
    // ここから，biggest[i]が収まるように座席を調整する
    // とりあえず，山登り法でやってみる
    constexpr double time_limit = 2800;
    auto start = chrono::system_clock::now();
    int cnt = 0;
    while (true)
    {
        cnt++;
        auto end = chrono::system_clock::now();
        double elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        if (elapsed > time_limit)
        {
            break;
        }
        for (int i = 0; i < N; i++)
        {
            int diff = biggest[i] - (seat[i].right_down.first - seat[i].left_up.first + 1) * (seat[i].right_down.second - seat[i].left_up.second + 1);
            if (diff == 0)
            {
                continue;
            }
            // diffが0になるように座席を調整する
            if (diff < 0)
            {
                // diffが負の場合，座席を縮める
                // 変化が少ない方向に縮める
                if (seat[i].right_down.first - seat[i].left_up.first > seat[i].right_down.second - seat[i].left_up.second)
                {
                    // 横幅を縮める
                    if (seat[i].right_down.first - seat[i].left_up.first > 1)
                    {
                        seat[i].right_down.first--;
                        for (int j = seat[i].left_up.second; j <= seat[i].right_down.second; j++)
                        {
                            assert(grid[seat[i].right_down.first][j] == i);
                            grid[seat[i].right_down.first][j] = -1;
                        }
                    }
                }
                else
                {
                    // 縦幅を縮める
                    if (seat[i].right_down.second - seat[i].left_up.second > 1)
                    {
                        seat[i].right_down.second--;
                        for (int j = seat[i].left_up.first; j <= seat[i].right_down.first; j++)
                        {
                            assert(grid[j][seat[i].right_down.second] == i);
                            grid[j][seat[i].right_down.second] = -1;
                        }
                    }
                }
            }
            else
            {
                // diffが正の場合，座席を広げる
                // 変化が多い方向に広げる
                if (seat[i].right_down.first - seat[i].left_up.first < seat[i].right_down.second - seat[i].left_up.second)
                {
                    // 横幅を広げる
                    if (can_put(seat[i].left_up, {seat[i].right_down.first + 1, seat[i].right_down.second}, i, grid, true))
                    {
                        seat[i].right_down.first++;
                        for (int j = seat[i].left_up.second; j <= seat[i].right_down.second; j++)
                        {
                            assert(grid[seat[i].right_down.first][j] == -1);
                            grid[seat[i].right_down.first][j] = i;
                        }
                    }
                }
                else
                {
                    // 縦幅を広げる
                    if (can_put(seat[i].left_up, {seat[i].right_down.first, seat[i].right_down.second + 1}, i, grid, false))
                    {
                        seat[i].right_down.second++;
                        for (int j = seat[i].left_up.first; j <= seat[i].right_down.first; j++)
                        {
                            assert(grid[j][seat[i].right_down.second] == -1);
                            grid[j][seat[i].right_down.second] = i;
                        }
                    }
                }
            }
        }
    }
    cerr << cnt << endl;
    for (int d = 0; d < D; d++)
    {
        for (auto [l, r] : seat)
        {
            cout << l.first << " " << l.second << " " << r.first << " " << r.second << endl;
        }
    }
}
