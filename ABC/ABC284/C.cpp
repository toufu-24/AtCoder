#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

void dfs(int v, vector<vector<int>> &G, vector<bool> &seen)
{
    seen[v] = true;
    for (auto v2 : G[v])
    {
        if (seen[v2])
        {
            continue;
        }
        dfs(v2, G, seen);
    }
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    for (int i = 0; i < M; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u-1].push_back(v-1);
        G[v-1].push_back(u-1);
    }

    vector<bool> seen(N, false);
    int ans = 0;
    for (int v = 0; v < N; v++)
    {
        if (seen[v])
        {
            continue;
        }
        dfs(v, G, seen);
        ans++;
    }
    cout << ans << endl;
}