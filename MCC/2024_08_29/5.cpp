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
    vector<int> a(m), b(m);
    vector<vector<int>> graph(n);
    dsu uf(n);
    bool ans = true;
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
        graph[a[i]].push_back(b[i]);
        graph[b[i]].push_back(a[i]);
        if (uf.same(a[i], b[i])) {
            ans = false;
        }
        uf.merge(a[i], b[i]);
    }

    vector<int> cnt(3, 0);
    for (int i = 0; i < n; i++) {
        if (graph[i].size() >= 3) {
            ans = false;
            break;
        }
        cnt[graph[i].size()]++;
    }
    if (ans) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
