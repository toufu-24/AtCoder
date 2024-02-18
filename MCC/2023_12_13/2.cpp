#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int H, W;
    cin >> H >> W;
    vector<vector<int>> c(10, vector<int>(10));
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            cin >> c[i][j];
        }
    }
    vector<vector<int>> A(H, vector<int>(W));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> A[i][j];
        }
    }
    vector<int> to1(10, 0);
    for (int num = 0; num <= 9; num++)
    {
        queue<pair<int, int>> q;
        q.push({num, 0});
        vector<int> dist(10, 1e9);
        dist[num] = 0;
        while (!q.empty())
        {
            auto [i, d] = q.front();
            q.pop();
            for (int j = 0; j <= 9; j++)
            {
                if (dist[j] > d + c[i][j])
                {
                    dist[j] = d + c[i][j];
                    q.push({j, dist[j]});
                }
            }
        }
        to1[num] = dist[1];
    }

    int ans = 0;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (A[i][j] == -1)
            {
                continue;
            }
            ans += to1[A[i][j]];
        }
    }
    cout << ans << endl;
}