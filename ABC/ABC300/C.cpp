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
    vector<vector<char>> C(H, vector<char>(W));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> C[i][j];
        }
    }
    int N = min(H, W);
    vector<int> ans(N + 1, 0);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (C[i][j] == '#')
            {
                int k = i, l = j;
                int cnt = 0;
                while (k < H && 0 <= k && l < W && 0 <= l && C[k][l] == '#')
                {
                    cnt++;
                    C[k][l] = '.';
                    k++;
                    l++;
                }
                k = i;
                for (int m = 0; m < cnt; m++)
                {
                    l--;
                    C[k][l] = '.';
                    k++;
                }
                ans[cnt / 2]++;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << ans[i + 1] << ' ';
    }
    cout << endl;
}