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

multiset<int> number;
vector<bool> ans;
vector<vector<int>> graph;
vector<bool> visited;
vector<int> a;
int cnt = 0;

void dfs(int now) {
    bool tmp = false;
    if (number.contains(a[now])) {
        cnt++;
        tmp = true;
    }
    if (cnt >= 1) {
        ans[now] = true;
    }
    visited[now] = true;
    number.insert(a[now]);
    for (auto next : graph[now]) {
        if (visited[next]) {
            continue;
        }
        dfs(next);
    }
    number.erase(number.find(a[now]));
    if (tmp) {
        cnt--;
    }
}

int32_t main() {
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ans.resize(n, false);
    visited.resize(n, false);

    graph.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(0);

    for (auto x : ans) {
        if (x) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
