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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
        graph[a[i]].push_back(b[i]);
        graph[b[i]].push_back(a[i]);
    }
    vector<int> v(k);
    for (int i = 0; i < k; i++) {
        cin >> v[i];
        v[i]--;
    }
    vector<int> ans;
    // vを頂点とする最小全域木を求める
}
