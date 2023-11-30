#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
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

    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == '#')
            {
                bool ok = false;
                for (int k = 0; k < 4; k++)
                {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (nx < 0 || nx >= H || ny < 0 || ny >= W)
                    {
                        continue;
                    }
                    if (S[nx][ny] == '#')
                    {
                        ok = true;
                    }
                }
                if (!ok)
                {
                    cout << "No" << endl;
                    return 0;
                }
            }
        }
    }
    cout << "Yes" << endl;
}