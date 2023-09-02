#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == '.')
            {
                S[i][j] = '0';
            }
        }
    }
    int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == '#')
            {
                for (int k = 0; k < 8; k++)
                {
                    int x = dx[k];
                    int y = dy[k];
                    if (i + x < 0 || i + x >= H || j + y < 0 || j + y >= W)
                    {
                        continue;
                    }
                    if (S[i + x][j + y] != '#')
                    {
                        // 周囲8だから二桁はない
                        S[i + x][j + y]++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < H; i++)
    {
        cout << S[i] << endl;
    }
}