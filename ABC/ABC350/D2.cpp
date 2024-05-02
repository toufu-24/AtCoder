#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph(N);
    vector<set<int>> edges(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
        edges[a].insert(b);
        edges[b].insert(a);
    }

    int cnt = 0;
    queue<int> q;
    q.push(0);
    vector<bool> visited(N, false);
    visited[0] = true;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int u : graph[v])
        {
            if (visited[u])
            {
                continue;
            }
            visited[u] = true;
            q.push(u);
            for (int w : graph[u])
            {
                if (edges[v].count(w))
                {
                    continue;
                }
                edges[v].insert(w);
                edges[w].insert(v);
                cnt++;
            }
        }
    }

    cout << cnt << endl;
}
