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

int32_t main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--, t--;
    vector<vector<int>> graph(n);
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
        graph[a[i]].push_back(b[i]);
    }
    for (int i = 0; i < n; i++) {
        SORT(graph[i]);
    }

    priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;
    pq.push({0, s});
    vector<int> dist(n, 1e9);
    dist[s] = 0;
    while (!pq.empty()) {
        auto [cost, now] = pq.top();
        pq.pop();

        if (dist[now] < cost) {
            continue;
        }

        int first = 0;
        for (auto ne : graph[now]) {
            first++;
            if (first == 1) {
                // コスト0

                if (dist[ne] <= cost) {
                    continue;
                }
                pq.push({cost, ne});
                dist[ne] = cost;

            } else {
                // コスト1
                if (dist[ne] <= cost + 1) {
                    continue;
                }
                pq.push({cost + 1, ne});
                dist[ne] = cost + 1;
            }
        }
    }
    if (dist[t] != 1e9) {
        cout << dist[t] << endl;
    } else {
        cout << -1 << endl;
    }
}
