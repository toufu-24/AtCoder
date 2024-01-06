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

int N, M;
int ans = 0;
vector<int> A;
vector<vector<int>> G;
void dfs(int v, vector<bool> visited, set<int> kind)
{
    visited[v] = true;
    for (int nv : G[v])
    {
        if (visited[nv])
        {
            continue;
        }
        if (A[nv] < A[v])
        {
            continue;
        }
        kind.insert(A[nv]);
        if (nv == N - 1)
        {
            ans = max(ans, (int)kind.size());
            continue;
        }
        dfs(nv, visited, kind);
        kind.erase(A[nv]);
    }
}

int32_t main()
{
    cin >> N >> M;
    A.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    G.resize(N);
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<bool> visited(N, false);
    set<int> kind;
    kind.insert(A[0]);
    dfs(0, visited, kind);
    cout << ans << endl;
}