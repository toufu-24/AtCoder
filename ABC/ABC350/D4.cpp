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
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int ans = 0;
    vector<bool> visited(N, false);
    for (int i = 0; i < N; i++)
    {
        // 連結成分内の辺の数を数える
        if (visited[i])
        {
            continue;
        }
        visited[i] = true;
        int edges = 0;
        int cnt = 1;
        queue<int> q;
        q.push(i);
        map<pair<int, int>, bool> mp;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (int u : graph[v])
            {
                if (mp[{v, u}] || mp[{u, v}])
                {
                    continue;
                }
                mp[{v, u}] = true;
                mp[{u, v}] = true;
                edges++;
                if (visited[u])
                {
                    continue;
                }
                visited[u] = true;
                q.push(u);
                cnt++;
            }
        }
        int tmp = cnt * (cnt - 1) / 2 - edges;
        ans += tmp;
    }

    cout << ans << endl;
}
