#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

void DFS(vector<vector<int>> &G, vector<int> &dist, int v, int d)
{
    dist[v] = d;
    for (int nv : G[v])
    {
        if (dist[nv] != -1 && dist[nv] < d + 1)
            continue;
        DFS(G, dist, nv, d + 1);
    }
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
        G[--a].emplace_back(--b);
        G[b].emplace_back(a);
    }
    // 頂点0の接続成分で一番遠い頂点を求める
    vector<int> dist1(N1, -1);
    DFS(G, dist1, 0, 0);
    int max_dist1 = 0;
    int max_dist1_idx = 0;
    for (int i = 0; i < N1; i++)
    {
        max_dist1 = max(max_dist1, dist1[i]);
        if (max_dist1 == dist1[i])
            max_dist1_idx = i;
    }

    // 頂点N1 + N2 -1の接続成分で一番遠い頂点を求める
    vector<int> dist2(N1 + N2, -1);
    DFS(G, dist2, N1 + N2 - 1, 0);
    int max_dist2 = 0;
    int max_dist2_idx = 0;
    for (int i = N2 - 1; i < N1 + N2; i++)
    {
        max_dist2 = max(max_dist2, dist2[i]);
        if (max_dist2 == dist2[i])
            max_dist2_idx = i;
    }

    cout << max_dist1 + max_dist2 + 1 << endl;
    // // 接続後に最短距離を求める
    // G[max_dist1_idx].push_back(max_dist2_idx);
    // G[max_dist2_idx].push_back(max_dist1_idx);
    // vector<int> dist3(N1 + N2, -1);
    // set<int> pass;
    // DFS(G, dist3, 0, 0);

    // cout << dist3[N1 + N2 - 1] << endl;
}