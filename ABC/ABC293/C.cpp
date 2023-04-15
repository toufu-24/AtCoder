#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int H, W;
    cin >> H >> W;
    vector<vector<int>> matrix(H + 1, vector<int>(W + 1));
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            cin >> matrix[i][j];
        }
    }
    vector<vector<vector<vector<int>>>> dp_set(H + 1, vector<vector<vector<int>>>(W + 1, vector<vector<int>>(1, vector<int>(1))));
    vector<vector<vector<int>>> dp(H + 1, vector<vector<int>>(W + 1, vector<int>()));
    dp[1][1].push_back(1);
    dp_set[1][1][0].push_back(matrix[1][1]);
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            for (int k = 0; k < dp_set[i - 1][j].size(); k++)
            {
                bool tate = true;
                for (int l = 0; l < dp_set[i - 1][j][k].size(); l++)
                {
                    if (dp_set[i][j][k][l] == matrix[i][j])
                    {
                        tate = false;
                        break;
                    }
                }
                if (!tate)
                {
                    dp_set[i][j].insert(dp_set[i][j].end(), all(dp_set[i - 1][j]));
                    dp_set[i][j][k].push_back(matrix[i][j]);
                    dp[i][j].push_back(dp[i - 1][j][k]);
                }
            }
            for (int k = 0; k < dp_set[i][j - 1].size(); k++)
            {
                bool tate = true;
                for (int l = 0; l < dp_set[i][j - 1][k].size(); l++)
                {
                    if (dp_set[i][j][k][l] == matrix[i][j])
                    {
                        tate = false;
                        break;
                    }
                }
                if (!tate)
                {
                    dp_set[i][j].insert(dp_set[i][j].end(), all(dp_set[i][j - 1]));
                    dp_set[i][j][k].push_back(matrix[i][j]);
                    dp[i][j].push_back(dp[i][j - 1][k]);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < dp[H][W].size(); i++)
    {
        ans += dp[H][W][i];
    }

    cout << dp[H][W].size();
}