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

struct ans_data {
    int before_x, before_y;
    int after_x, after_y;
};
int n = 1000;
void output(vector<ans_data> &ans) {
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].before_x << " " << ans[i].before_y << " " << ans[i].after_x << " " << ans[i].after_y << endl;
    }
}

int32_t main() {
    ld start = clock();
    constexpr ld TIME_LIMIT = 1.9 * CLOCKS_PER_SEC;
    int _n;
    cin >> _n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<pair<int, int>> a_b(n);
    for (int i = 0; i < n; i++) {
        a_b[i] = {a[i], b[i]};
    }
    a_b.insert(a_b.begin(), {0, 0});
    n++;
    struct edge {
        int to, cost;
    };

    vector<vector<edge>> graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (a_b[i].first <= a_b[j].first && a_b[i].second <= a_b[j].second) {
                graph[i].push_back({j, abs(a_b[i].first - a_b[j].first) + abs(a_b[i].second - a_b[j].second)});
            }
        }
    }

    vector<pair<int, int>> ans_idx;
    // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    vector<int> dist(n, 1e18);
    pq.push({0, 0, 0});
    dist[0] = 0;
    while (!pq.empty()) {
        auto [d, v, p] = pq.top();
        pq.pop();
        if (dist[v] < d) {
            continue;
        }
        ans_idx.push_back({v, p});
        for (auto u : graph[v]) {
            if (dist[u.to] > u.cost) {
                dist[u.to] = u.cost;
                pq.push({dist[u.to], u.to, v});
            }
        }
    }

    vector<ans_data> ans;
    for (int i = 1; i < ans_idx.size(); i++) {
        ans.push_back({a_b[ans_idx[i].second].first, a_b[ans_idx[i].second].second, a_b[ans_idx[i].first].first, a_b[ans_idx[i].first].second});
    }
    output(ans);
}
