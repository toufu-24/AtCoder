#pragma GCC target("avx2")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    vector<int> player;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (S[i][j] == 'P')
            {
                player.push_back(i);
                player.push_back(j);
            }
        }
    }

    queue<vector<int>> q;
    q.push(player);
    set<vector<int>> visited;
    visited.insert(player);
    auto fix = [&](int x) -> int
    {
        if (x < 0)
        {
            return 0;
        }
        if (x >= N)
        {
            return N - 1;
        }
        return x;
    };

    vector dist(N, vector(N, vector(N, vector<int>(N, 1e9))));
    dist[player[0]][player[1]][player[2]][player[3]] = 0;

    while (!q.empty())
    {
        vector<int> now;
        now = q.front();
        q.pop();
        for (int m = 0; m < 4; m++)
        {
            int ni = fix(now[0] + dx[m]);
            int nj = fix(now[1] + dy[m]);
            int nk = fix(now[2] + dx[m]);
            int nl = fix(now[3] + dy[m]);
            if (S[ni][nj] == '#')
            {
                ni = now[0];
                nj = now[1];
            }
            if (S[nk][nl] == '#')
            {
                nk = now[2];
                nl = now[3];
            }
            if (dist[ni][nj][nk][nl] != 1e9)
            {
                continue;
            }
            if (ni == now[0] && nj == now[1] && nk == now[2] && nl == now[3])
            {
                continue;
            }
            dist[ni][nj][nk][nl] = dist[now[0]][now[1]][now[2]][now[3]] + 1;
            q.push({ni, nj, nk, nl});
        }
    }

    int ans = 1e9;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            ans = min(dist[i][j][i][j], ans);
        }
    }
    if (ans == 1e9)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << ans << endl;
    }
}