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
    }
    vector<vector<bool>> sirusi(H, vector<bool>(W, false));
    for (int i = 0; i < H; i++)
    {
        map<char, pair<int, int>> s;
        for (int j = 0; j < W; j++)
        {
            if (s.count(S[i][j]))
            {
                auto zahyou = s[S[i][j]];
                int x = zahyou.first;
                int y = zahyou.second;
                sirusi[i][j] = false;
                sirusi[x][y] = false;
            }
            else
            {
                sirusi[i][j] = true;
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (sirusi[i][j])
            {
                cnt++;
            }
        }
    }
    cout << cnt << endl;
}