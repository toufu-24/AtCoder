#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> a(N);
    scc_graph scc_g(N);
    vector<vector<int>> g(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        a[i]--;
        g[i].push_back(a[i]);
        scc_g.add_edge(i, a[i]);
    }
    auto scc = scc_g.scc();
    vector<int> visitable(N, -1);
    vector<bool> visited(N, false);
    auto dfs = [&](int v, int cnt, auto &&dfs) -> int
    {
        visited[v] = true;
        // if (visitable[v] != -1)
        //     return visitable[v];
        int ret = 0;
        for (int u : g[v])
        {
            if (!visited[u])
            {
                ret += dfs(u, cnt + 1, dfs);
            }
        }
        return visitable[v] = ret + cnt;
    };
    int ans = 0;
    for (auto &v : scc)
    {
        fill(visited.begin(), visited.end(), false);
        int cnt = dfs(v[0], 0, dfs) + 1;
        ans += cnt * v.size();
    }
    cout << ans << endl;
}
