#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

// struct edge
// {
//     int to;
//     bool able_through;
// };

int main()
{
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> G(N);
    vector<vector<int>> G2(N);
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
        if (able_through)
        {
            G[u].push_back(v);
            G[v].push_back(u);
        }
        else
        {
            G2[u].push_back(v);
            G2[v].push_back(u);
        }
    }

    queue<pair<int, bool>> q;
    q.push({0, true});
    vector<int> dist(N, 1e9);
    vector<int> dist2(N, 1e9);
    dist[0] = 0;
    while (!q.empty())
    {
        int now;
        bool omote;
        tie(now, omote) = q.front();
        q.pop();
        if (omote)
        {
            for (auto e : G[now])
            {
                if (dist[e] > dist[now] + 1)
                {
                    dist[e] = dist[now] + 1;
                    q.push({e, true});
                }
            }
            if (st.count(now))
            {
                for (auto e : G2[now])
                {
                    if (dist2[e] > dist[now] + 1)
                    {
                        dist2[e] = dist[now] + 1;
                        q.push({e, false});
                    }
                }
            }
        }
        else
        {
            for (auto e : G2[now])
            {
                if (dist2[e] > dist2[now] + 1)
                {
                    dist2[e] = dist2[now] + 1;
                    q.push({e, false});
                }
            }
            if (st.count(now))
            {
                for (auto e : G[now])
                {
                    if (dist[e] > dist2[now] + 1)
                    {
                        dist[e] = dist2[now] + 1;
                        q.push({e, true});
                    }
                }
            }
        }
    }
    if (min(dist[N - 1], dist2[N - 1]) == 1e9)
    {
        cout << -1;
    }
    else
    {
        cout << min(dist[N - 1], dist2[N - 1]);
    }
}