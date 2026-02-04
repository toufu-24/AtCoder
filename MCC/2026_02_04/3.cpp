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
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        // graph[x].push_back(y);
        graph[y].push_back(x);
    }
    int q;
    cin >> q;
    vector<bool> reachable(n, false);
    while (q--) {
        int op, v;
        cin >> op >> v;
        v--;
        if (op == 1) {
            queue<int> que;
            que.push(v);
            if (reachable[v]) {
                continue;
            }
            reachable[v] = true;
            while (!que.empty()) {
                int now = que.front();
                que.pop();
                for (auto next : graph[now]) {
                    if (reachable[next]) {
                        continue;
                    }
                    reachable[next] = true;
                    que.push(next);
                }
            }
        } else {
            if (reachable[v]) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
}
