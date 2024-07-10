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

vector<int> ans;
vector<vector<int>> graph;
vector<bool> visited;
void dfs(int v) {
    ans.push_back(v);
    bool exist = false;
    for (auto next : graph[v]) {
        if (visited[next]) {
            continue;
        }
        visited[next] = true;
        exist = true;
        dfs(next);
        ans.push_back(v);
    }
}

int32_t main() {
    int N;
    cin >> N;
    graph.resize(N, vector<int>());
    visited.resize(N, false);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        SORT(graph[i]);
    }
    visited[0] = true;
    dfs(0);
    for (auto x : ans) {
        cout << x + 1 << " ";
    }
}
