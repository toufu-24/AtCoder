#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())

int main()
{
    int H, W;
    cin >> H >> W;
    vector<vector<char>> C(H, vector<char>(W));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> C[i][j];
        }
    }
    vector<int> ans(W, 0);
    for (int j = 0; j < W; j++)
    {
        for (int i = 0; i < H; i++)
        {
            if (C[i][j] == '#')
            {
                ans[j]++;
            }
        }
    }
    for (int i = 0; i < W; i++)
    {
        cout << ans[i] << " ";
    }
}