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
    int to, weight, idx;
};

int32_t main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    vector<vector<edge>> graph(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        graph[a].push_back({b, w, i});
        graph[b].push_back({a, w, i});
    }
    // 重み, 初期値idx, 現在頂点
    // queue<tuple<int, int, int>> q;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> q;
    for (int i = 0; i < n; i++) {
        if (x[i] > 0) {
            q.push({0, i, i});
        }
    }
    while (!q.empty()) {
        auto [weight, idx, v] = q.top();
        q.pop();
        int dennshi_num = x[idx];
        for (auto [to, w, i] : graph[v]) {
            if (x[to] >= 0) {
                q.push({weight + w * dennshi_num, i, to});
            } else {
                int minner = min(dennshi_num, x[to]);
                x[to] -= minner;
                dennshi_num -= minner;
            }
        }
    }
}
