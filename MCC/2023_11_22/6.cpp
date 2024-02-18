#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

struct edge
{
    int to;
    bool able_through;
};

int main()
{
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<edge>> G(2 * N);
    set<int> st;
    vector<vector<int>> input;
    for (int i = 0; i < M; i++)
    {
        int u, v, a;
        cin >> u >> v >> a;
        u--;
        v--;
        input.push_back({u, v, a});
    }
    for (int i = 0; i < K; i++)
    {
        int s;
        cin >> s;
        s--;
        st.insert(s);
    }
    for (int i = 0; i < M; i++)
    {
        int u, v, a;
        u = input[i][0];
        v = input[i][1];
        a = input[i][2];

        bool able_through = (a == 1);
        if (st.count(u))
        {
            G[u + N].push_back({v, !able_through});
            G[u + N].push_back({v + N, !able_through});
        }
        if (st.count(v))
        {
            G[v + N].push_back({u, !able_through});
            G[v + N].push_back({u + N, !able_through});
        }
        G[u].push_back({v, able_through});
        G[v].push_back({u, able_through});
    }

    queue<int> q;
    q.push(0);
    vector<int> dist(2 * N, 1e9);
    dist[0] = 0;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (auto e : G[now])
        {
            if (dist[e.to] > dist[now] + 1 && e.able_through)
            {
                dist[e.to] = dist[now] + 1;
                q.push(e.to);
            }
        }
    }
    if (min(dist[N - 1], dist[N + N - 1]) == 1e9)
    {
        cout << -1;
    }
    else
    {
        cout << min(dist[N - 1], dist[N + N - 1]);
    }
}