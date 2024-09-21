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

using mint = modint998244353;

int32_t main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        graph[i].push_back((i + 1) % n);
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        graph[x].push_back(y);
    }

    mint ans = 0;
}
