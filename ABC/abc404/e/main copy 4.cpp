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
    int n;
    cin >> n;
    vector<int> c(n, -1), a(n, 0);
    for (int i = 1; i < n; i++) {
        cin >> c[i];
    }
    int not_zero = 0;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
        if (a[i] != 0) {
            not_zero++;
        }
    }
    // vector<int> now_arr(n, 0);
    // now_arr[0] = reduce(all(a), 0);
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= c[i]; j++) {
            int ni = i - j;
            if (ni < 0) {
                break;
            }
            graph[ni].push_back(i);
        }
    }
    assert(graph[n - 1].size() == 0);
    for (int i = 0; i < n; i++) {
        for (auto g : graph[i]) {
            assert(i < g);
        }
    }

    int ans = 1e18;
    // auto dfs = [&](auto dfs, int now_not_zero_cnt, int now_index, int now_dist) -> void {
    //     if (now_not_zero_cnt == not_zero) {
    //         ans = min(ans, now_dist);
    //         return;
    //     }
    //     for (auto g : graph[now_index]) {
    //         if (a[g] == 0) {
    //             dfs(dfs, now_not_zero_cnt, g, now_dist + 1);
    //         } else {
    //             dfs(dfs, now_not_zero_cnt + 1, g, now_dist + 1);
    //         }
    //     }
    // };
    // dfs(dfs, 0, 0, 0);
    queue<pair<int, int>> que;
    que.push({0, 0});
    vector<vector<int>> dist(n, vector<int>(not_zero + 1, 1e18));
    dist[0][0] = 0;
    if (a[0] != 0) {
        dist[0][1] = 0;
    }
    while (!que.empty()) {
        auto [now_index, now_dist] = que.front();
        que.pop();
        for (auto g : graph[now_index]) {
            if (a[g] == 0) {
                if (dist[g][now_dist] > dist[now_index][now_dist] + 1) {
                    dist[g][now_dist] = dist[now_index][now_dist] + 1;
                    que.push({g, now_dist});
                }
            } else {
                if (dist[g][now_dist + 1] > dist[now_index][now_dist] + 1) {
                    dist[g][now_dist + 1] = dist[now_index][now_dist] + 1;
                    que.push({g, now_dist + 1});
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        ans = min(ans, dist[i][not_zero]);
    }

    cout << ans << endl;
}
