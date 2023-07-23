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
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (auto v : G[i])
        {
            for (auto w : G[v])
            {
                if (w == i)
                {
                    continue;
                }
                for (auto x : G[w])
                {
                    if (x == i)
                    {
                        ans++;
                    }
                }
            }
        }
    }
    cout << ans / 6;
}