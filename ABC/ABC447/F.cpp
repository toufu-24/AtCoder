#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        vector<vector<int>> graph(n);
        vector<pair<int, int>> edges;
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            graph[a].push_back(b);
            graph[b].push_back(a);
            edges.push_back({a, b});
        }

        // set<int> four, three;
        vector<bool> four(n, false), three(n, false);
        for (int i = 0; i < n; i++) {
            if (graph[i].size() >= 4) {
                four[i] = true;
            }
            if (graph[i].size() == 3) {
                three[i] = true;
            }
        }

        // 最初と最後だけthreeでもいい，fourで構築される木の直径で最大のもの
        dsu four_con(n);
        for (auto [u, v] : edges) {
            if (four[u] && four[v]) {
                four_con.merge(u, v);
            }
        }

        int ans = 0;
        auto g = four_con.groups();
        for (auto con : g) {
            // https://qiita.com/nomikura/items/a4c5be6c72ce854d7ce4
            // treeDFS(親, 現在地, 根から現在地までの距離, 根からの最大の距離, 根から最大の距離となる頂点
            auto dfs = [&](auto dfs, int from, int current, int dist, int &maxDist, int &maxVertex) -> void {
                // 距離と終点を更新
                if (dist > maxDist) {
                    maxDist = dist;
                    maxVertex = current;
                }

                int cnt = 0;
                for (auto to : graph[current]) {
                    // 逆流を防ぐ
                    if (to == from)
                        continue;
                    if (!four[to]) {
                        continue;
                    }
                    cnt++;
                    dfs(dfs, current, to, dist + 1, maxDist, maxVertex);
                }
                if (cnt == 0) {
                    for (auto to : graph[current]) {
                        // 逆流を防ぐ
                        if (to == from)
                            continue;
                        if (three[to]) {
                            if (dist + 1 > maxDist) {
                                maxDist = dist + 1;
                                maxVertex = to;
                            }
                            break;
                        }
                    }
                }
            };

            int start = con[0], end = con[0], maxDist = 0;
            dfs(dfs, -1, start, 0, maxDist, end);
            start = end, end = end, maxDist = 0;
            dfs(dfs, -1, start, 0, maxDist, end);

            ans = max(ans, maxDist);
        }
        cout << ans + 1 << '\n';
    }
}
