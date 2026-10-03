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
    int type;
    int to;
};

int32_t main() {
    int n, q;
    cin >> n >> q;
    vector<int> cnt(n, 0);
    vector<vector<edge>> graph(n);
    for (int i = 0; i < q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        u--, v--;
        t++;
        graph[u].push_back({t, v});
        // graph[v].push_back({-t, u});
        cnt[v]++;
    }

    // type = 1を含む閉路がある？
    bool ok = true;
    vector<int> ans(n, -1e9);
    vector<bool> seen(n, false);
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1e9) {
            continue;
        }
        ans[i] = 0;
        priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> que;
        que.push({0, i});
        while (!que.empty()) {
            auto [co, now] = que.top();
            que.pop();
            if (seen[now]) {
                continue;
            }
            seen[now] = true;
            for (auto [t, v] : graph[now]) {
                if (ans[v] != -1e9) {
                    // 矛盾検知
                    if (t == -1) {
                        ok &= (ans[v] <= ans[now]);
                    }
                    if (t == -2) {
                        ok &= (ans[v] < ans[now]);
                    }
                    if (t == 1) {
                        ok &= (ans[v] >= ans[now]);
                    }
                    if (t == 2) {
                        ok &= (ans[v] > ans[now]);
                    }
                    continue;
                }

                if (t == -1) {
                    ans[v] = ans[now];
                }
                if (t == -2) {
                    ans[v] = ans[now] - 1;
                }
                if (t == 1) {
                    ans[v] = ans[now];
                }
                if (t == 2) {
                    ans[v] = ans[now] + 1;
                }
                que.push(v);
            }
            if (!ok) {
                goto en;
            }
        }
    }
en:;
    if (ok) {
        cout << "Yes" << endl;
        for (auto x : ans) {
            cout << x << " ";
        }
    } else {
        cout << "No" << endl;
    }
}
