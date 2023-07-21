#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

void DFS(vector<vector<int>> &G, vector<int> &dist, int v, int d, set<int> &pass)
{
    if (dist[v] < d)
    {
        dist[v] = d;
    }
    pass.insert(v);
    for (int nv : G[v])
    {
        if (pass.count(nv))
            continue;
        DFS(G, dist, nv, d + 1, pass);
    }
    pass.erase(v);
}

int main()
{
    int N1, N2, M;
    cin >> N1 >> N2 >> M;
    vector<vector<int>> G(N1 + N2);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        G[--a].push_back(--b);
        G[b].push_back(a);
    }
    // 頂点0の接続成分で一番遠い頂点を求める
    // 最長距離じゃないとだめだね
    vector<int> dist1(N1, -1);
    set<int> pass;
    DFS(G, dist1, 0, 0, pass);
    int max_dist1 = 0;
    for (int i = 0; i < N1; i++)
        max_dist1 = max(max_dist1, dist1[i]);

    // 頂点N2の接続成分で一番遠い頂点を求める
    vector<int> dist2(N1 + N2, -1);
    pass.clear();
    DFS(G, dist2, N1 + N2 - 1, 0, pass);
    int max_dist2 = 0;
    for (int i = N2 - 1; i < N1 + N2; i++)
        max_dist2 = max(max_dist2, dist2[i]);

    cout << max_dist1 + max_dist2 << endl;
}