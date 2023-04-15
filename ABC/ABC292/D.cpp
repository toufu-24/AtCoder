#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
using ll = long long;
int N, M;

int loop_cnt = 0; // ループの個数

void dfs(int v, int p, vector<bool> &used, vector<vector<int>> &G)
{
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++)
    {
        int to = G[v][i];
        if (!used[to])
        {
            dfs(to, v, used, G);
        }
        else if (to != p)
        {
            loop_cnt++;
        }
    }
}

void dfs2(int v, vector<vector<int>> &G, vector<bool> &seen)
{
    seen[v] = true;
    for (auto v2 : G[v])
    {
        if (seen[v2])
        {
            continue;
        }
        dfs2(v2, G, seen);
    }
    return;
}

int main()
{
    cin >> N >> M;
    vector<vector<int>> G(N + 1);
    for (int i = 0; i < M; i++)
    {
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        G[tmp1].push_back(tmp2);
        G[tmp2].push_back(tmp1);
    }
    if (N != M)
    {
        cout << "No";
        return 0;
    }
    vector<bool> used(N, false);
    for (int i = 1; i <= N; i++)
    {
        if (!used[i])
        {
            dfs(i, -1, used, G);
        }
    }
    vector<bool> seen(N, false);
    int ans = 0;
    for (int v = 1; v <= N; ++v)
    {
        if (seen[v])
        {
            continue;
        }
        dfs2(v, G, seen);
        ans++;
    }
    if (ans == loop_cnt)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}