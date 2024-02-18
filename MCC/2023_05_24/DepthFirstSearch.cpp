#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int N, M;
vector<vector<int>> G;
vector<bool> exist;

void dfs(int v)
{
    exist[v] = true;
    for (int i = 0; i < G[v].size(); i++)
    {
        if (!exist[G[v][i]])
        {
            dfs(G[v][i]);
        }
    }
}

int main()
{
    cin >> N >> M;
    G.resize(N);
    exist.resize(N, false);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 0; i < G[0].size(); i++)
    {
        dfs(G[0][i]);
    }

    bool ans = true;
    for (int i = 1; i < exist.size(); i++)
    {
        if (!exist[i])
        {
            ans = false;
            break;
        }
    }

    if (ans)
    {
        cout << "The graph is connected.";
    }
    else
    {
        cout << "The graph is not connected.";
    }
}