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
    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    p[0] = -1;
    vector<vector<int>> graph(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        graph[p[i]].push_back(i);
    }

    priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;
    vector<int> x(m), y(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i] >> y[i];
        x[i]--;
        pq.push({x[i], -y[i]});
    }

    set<int> ok;
    vector<int> remain_insurance(n, -1);
    while (!pq.empty()) {
        auto [v, remain] = pq.top();
        pq.pop();
        ok.insert(v);
        remain *= -1;
        if (remain_insurance[v] >= remain) {
            continue;
        }
        remain_insurance[v] = remain;
        if (remain == 0) {
            continue;
        }
        for (auto next : graph[v]) {
            ok.insert(next);
            if (remain_insurance[next] >= remain - 1) {
                continue;
            }
            pq.push({next, -(remain - 1)});
        }
    }

    // for (auto x : ok) {
    //     cerr << x << ' ';
    // }
    // cerr << endl;
    cout << ok.size() << endl;
}
