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
    int N;
    cin >> N;
    vector<vector<pair<int, int>>> G(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        G[a].push_back({b, i});
        G[b].push_back({a, i});
    }

    queue<int> q;
    int st = 0, size = 0;
    for (int i = 0; i < N; i++) {
        if (G[i].size() > size) {
            st = i;
            size = G[i].size();
        }
    }
    vector<int> color(N - 1, -1);
    vector<set<int>> used(N);
    int color_cnt = 0;
    for (auto x : G[st]) {
        color[x.second] = color_cnt++;
        used[st].insert(color[x.second]);
        used[x.first].insert(color[x.second]);
        q.push(x.first);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto [next, idx] : G[v]) {
            if (color[idx] != -1) continue;
            // 頂点のどっちにも接続してない最小の色を塗る
            int min_color = 0;
            while (used[v].contains(min_color) || used[next].contains(min_color)) {
                min_color++;
            }
            color[idx] = min_color;
            used[v].insert(min_color);
            used[next].insert(min_color);
            q.push(next);
        }
    }

    int ans = 0;
    for (int i = 0; i < N - 1; i++) {
        ans = max(ans, color[i] + 1);
    }
    cout << ans << endl;
    for (int i = 0; i < N - 1; i++) {
        cout << color[i] + 1 << endl;
    }
}
