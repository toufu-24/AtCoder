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
    for (int i = 1; i < n; i++) {
        cin >> a[i];
    }
    vector<int> now_arr(n, 0);
    now_arr[0] = reduce(all(a), 0);
    int ans = 0;
    vector<int> dist(n, 1e18);
    // 0->iへの最短距離
    dist[0] = 0;
    queue<int> que;
    que.push(0);
    while (!que.empty()) {
        int now = que.front();
        que.pop();
        for (int i = now; i < n; i++) {
            if (i - c[i] > now) {
                continue;
            }
            if (dist[i] > dist[now] + 1) {
                dist[i] = dist[now] + 1;
                que.push(i);
            }
        }
    }
    for (auto d : dist) {
        cerr << d << " ";
    }
    cerr << endl;
    // 経路復元
}
