#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int N, M;
vector<vector<int>> G;

int main()
{
    cin >> N >> M;
    G.resize(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    queue<int> que;
    que.push(0);
    vector<int> ans(N, INT32_MAX);
    ans[0] = 0;
    while (!que.empty())
    {
        int v = que.front();
        que.pop();
        for (int i = 0; i < G[v].size(); i++)
        {
            if (ans[G[v][i]] > ans[v] + 1)
            {
                ans[G[v][i]] = ans[v] + 1;
                que.push(G[v][i]);
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (ans[i] == INT32_MAX)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << ans[i] << endl;
        }
    }
}