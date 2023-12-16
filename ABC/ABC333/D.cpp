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

vector<vector<int>> G;
vector<bool> seen;
int dfs(int now)
{
    if (seen[now])
        return 1;
    seen[now] = true;
    int res = 1;
    for (auto next : G[now])
    {
        if (seen[next])
            continue;
        res += dfs(next);
    }
    return res;
}

int main()
{
    int N;
    cin >> N;
    G.resize(N);
    seen.resize(N);
    for (int i = 0; i < N - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    seen[0] = true;
    vector<int> dfs_res;
    for (auto next : G[0])
    {
        dfs_res.push_back(dfs(next));
    }
    SORT(dfs_res);
    cout << reduce(all(dfs_res), 0) - dfs_res[dfs_res.size() - 1] + 1 << endl;
}