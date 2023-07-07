#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int H, W;
    cin >> H >> W;
    vector<vector<char>> S(H, vector<char>(W));
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            cin >> S[i][j];
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};
    pair<int, int> ans;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == '.')
            {
                int cnt = 0;
                for (int k = 0; k < 4; k++)
                {
                    if (i + dy[k] < 0 || i + dy[k] >= H || j + dx[k] < 0 || j + dx[k] >= W)
                        continue;
                    if (S[i + dy[k]][j + dx[k]] == '#')
                        cnt++;
                }
                if (cnt >= 2)
                {
                    ans.first = i + 1;
                    ans.second = j + 1;
                    break;
                }
            }
        }
    }
    cout << ans.first << " " << ans.second;
}