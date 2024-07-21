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

struct edge {
    int to, cost;
};

int32_t main() {
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    vector<vector<edge>> g(N);
    for (int i = 0; i < M; i++) {
        int u, v, b;
        cin >> u >> v >> b;
        u--;
        v--;
        g[u].push_back({v, b});
        g[v].push_back({u, b});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(N, 1e18);
    pq.push({A[0], 0});
    dist[0] = A[0];
    while (!pq.empty()) {
        auto [cost, now] = pq.top();
        pq.pop();
        if (dist[now] < cost) {
            continue;
        }
        for (auto [to, c] : g[now]) {
            if (dist[to] > cost + A[to] + c) {
                dist[to] = cost + A[to] + c;
                pq.push({dist[to], to});
            }
        }
    }

    for (int i = 1; i < N; i++) {
        cout << dist[i] << " ";
    }
}
