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

#define int ll

struct tile
{
    int height, width;
    int index;
};

int N, H, W;
vector<int> A, B;
vector<tile> tiles;
bool ans = false;

bool ok(vector<vector<bool>> &grid)
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (grid[i][j] == false)
            {
                return false;
            }
        }
    }
    return true;
}

bool dfs(set<int> &unused, vector<vector<bool>> &grid)
{
    vector<vector<bool>> original = grid;
    set<int> tmp_unused = unused;
    // どこに置けるかを探す
    for (auto idx : unused)
    {
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                if (!grid[i][j])
                {
                    // 通常
                    bool can_put = true;
                    for (int k = 0; k < tiles[idx].height; k++)
                    {
                        for (int l = 0; l < tiles[idx].width; l++)
                        {
                            if (i + k >= H || j + l >= W)
                            {
                                can_put = false;
                                goto rotate;
                            }
                            if (grid[i + k][j + l])
                            {
                                can_put = false;
                                goto rotate;
                            }
                        }
                    }
                    if (can_put)
                    {
                        for (int k = 0; k < tiles[idx].height; k++)
                        {
                            for (int l = 0; l < tiles[idx].width; l++)
                            {
                                grid[i + k][j + l] = true;
                            }
                        }
                        tmp_unused.erase(idx);
                        if (ok(grid))
                        {
                            ans = true;
                            return true;
                        }
                        if (dfs(tmp_unused, grid))
                        {
                            return true;
                        }
                        grid = original;
                        tmp_unused.insert(idx);
                    }
                rotate:
                    // 90度回転
                    can_put = true;
                    for (int k = 0; k < tiles[idx].width; k++)
                    {
                        for (int l = 0; l < tiles[idx].height; l++)
                        {
                            if (i + k >= H || j + l >= W)
                            {
                                can_put = false;
                                goto next;
                            }
                            if (grid[i + k][j + l])
                            {
                                can_put = false;
                                goto next;
                            }
                        }
                    }
                    if (can_put)
                    {
                        for (int k = 0; k < tiles[idx].width; k++)
                        {
                            for (int l = 0; l < tiles[idx].height; l++)
                            {
                                grid[i + k][j + l] = true;
                            }
                        }
                        tmp_unused.erase(idx);
                        if (ok(grid))
                        {
                            ans = true;
                            return true;
                        }
                        if (dfs(tmp_unused, grid))
                        {
                            return true;
                        }
                        grid = original;
                        tmp_unused.insert(idx);
                    }
                next:;
                    goto new_tile;
                }
            }
        }
    new_tile:;
    }
    return false;
}

int32_t main()
{
    cin >> N >> H >> W;
    A.resize(N);
    B.resize(N);
    tiles.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i] >> B[i];
        tiles[i] = {A[i], B[i], i};
    }
    // 回転したり裏返したり -> 長方形なので回転しか考えないでいい
    set<int> unused;
    for (int i = 0; i < N; i++)
    {
        unused.insert(i);
    }
    vector<vector<bool>> grid(H, vector<bool>(W, false));
    dfs(unused, grid);
    if (ans)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}