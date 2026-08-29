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

// #define int ll

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> ans;
    // [0]捨て
    vector<int> init(n + 1, 0);
    queue<tuple<int, int, vector<int>>> q;
    q.push({k, n, init});

    // 上から決めてく
    while (!q.empty()) {
        auto [nokori, now_idx, now] = q.front();
        q.pop();
        int now_now_idx = now[now_idx];

        if (now_idx - 1 == 0) {
            now[now_idx] = nokori;
            ans.push_back(now);
            continue;
        }
        for (int i = 0; i * now_idx <= nokori; i++) {
            now[now_idx] = now_now_idx;
            auto &ne = now;
            ne[now_idx] = i;
            int ne_nokori = nokori - i * now_idx;
            assert(ne_nokori >= 0);
            if (ne_nokori == 0) {
                ans.push_back(ne);
                continue;
            }
            // if (now_idx - 1 == 0) {
            //     continue;
            // }
            q.push({ne_nokori, now_idx - 1, ne});
        }
    }
    SORT(ans);

    for (auto &v : ans) {
        for (int i = 1; i <= n; i++) {
            cout << v[i] << " ";
        }
        cout << "\n";
    }
}
