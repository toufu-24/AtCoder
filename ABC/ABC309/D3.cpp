#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

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
    vector<int> dist1(N1, -1);
    queue<int> q;
    q.push(0);
    dist1[0] = 0;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int nv : G[v])
        {
            if (dist1[nv] != -1)
                continue;
            dist1[nv] = dist1[v] + 1;
            q.push(nv);
        }
    }
    int max_dist1 = 0;
    for (int i = 0; i < N1; i++)
        max_dist1 = max(max_dist1, dist1[i]);

    // 頂点N2の接続成分で一番遠い頂点を求める
    vector<int> dist2(N1 + N2, -1);
    q.push(N1 + N2 - 1);
    dist2[N1 + N2] = 0;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int nv : G[v])
        {
            if (dist2[nv] != -1)
                continue;
            dist2[nv] = dist2[v] + 1;
            q.push(nv);
        }
    }
    int max_dist2 = 0;
    for (int i = N2; i < N1 + N2; i++)
        max_dist2 = max(max_dist2, dist2[i]);

    cout << max_dist1 + max_dist2 << endl;
}