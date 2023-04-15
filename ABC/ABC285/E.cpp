#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int ans = 0;
int cnt = 0;

void dfs(int v, vector<vector<int>> &G, vector<bool> &seen)
{
    if (ans > 1000000)
    {
        ans = 1000000;
        return;
    }
    seen[v] = true;
    for (auto v2 : G[v])
    {
        if (seen[v2])
        {
            continue;
        }
        dfs(v2, G, seen);
        ans++;
        seen[v2] = false;
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
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }

    vector<bool> seen(N, false);
    dfs(0, G, seen);
    ans++;

    if (ans > 1000000)
    {
        ans = 1000000;
    }

    cout << ans << endl;
}
