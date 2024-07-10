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
    vector<vector<int>> graph(N);
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

    vector<int> parent(N, -1);
    parent[0] = 0;
    vector<int> ans;
    ans.push_back(0);
    int now = 0;
    while (true) {
        bool exist = false;
        for (auto next : graph[now]) {
            if (parent[next] == -1) {
                ans.push_back(next);
                parent[next] = now;
                now = next;
                exist = true;
                break;
            }
        }
        if (!exist) {
            if (now == 0) {
                break;
            }
            ans.push_back(parent[now]);
            now = parent[now];
        }
    }

    for (auto x : ans) {
        cout << x + 1 << " ";
    }
}
