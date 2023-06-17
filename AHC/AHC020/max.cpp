#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    ll N, M, K;
    cin >> N >> M >> K;
    vector<pair<ll, ll>> Broadcaster(N);
    for (ll i = 0; i < N; i++)
    {
        ll x, y;
        cin >> x >> y;
        Broadcaster[i] = make_pair(x, y);
    }
    vector<vector<ll>> graph(N, vector<ll>(N, -1));
    vector<vector<ll>> edge(M, vector<ll>(M, -1));
    for (ll i = 0; i < M; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        graph[u][v] = w;
        graph[v][u] = w;
        edge[i] = {u, v, w};
    }

    vector<pair<ll, ll>> people(K);
    for (ll i = 0; i < K; i++)
    {
        ll x, y;
        cin >> x >> y;
        people[i] = make_pair(x, y);
    }

    for (int i = 0; i < N; i++)
    {
        cout << "5000 ";
    }
    cout << endl;
    for (int i = 0; i < M; i++)
    {
        cout << "1 ";
    }
    
}