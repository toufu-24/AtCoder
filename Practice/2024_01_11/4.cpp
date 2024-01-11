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
int H, W;
vector<string> S;
pair<int, int> start;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool dfs(int x, int y, vector<vector<bool>> &seen, int depth)
{
    if (x < 0 || x >= H || y < 0 || y >= W || S[x][y] == '#')
    {
        return false;
    }
    if (S[x][y] == 'S')
    {
        if (depth + 1 >= 4)
        {
            return true;
        }
    }
    if (seen[x][y])
    {
        return false;
    }
    seen[x][y] = true;
    for (int i = 0; i < 4; i++)
    {
        if (dfs(x + dx[i], y + dy[i], seen, depth + 1))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> H >> W;
    S.resize(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == 'S')
            {
                start = {i, j};
            }
        }
    }
    vector<vector<bool>> seen(H, vector<bool>(W, false));
    if (dfs(start.first, start.second, seen, 0))
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}