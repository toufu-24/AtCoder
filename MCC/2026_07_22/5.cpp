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
    vector<int> b(n);
    for (int i = 1; i < n; i++) {
        cin >> b[i];
        b[i]--;
    }
    vector<vector<int>> graph(n);
    for (int i = 1; i < n; i++) {
        graph[b[i]].push_back(i);
    }

    vector<int> ans(n);
    auto dfs = [&](auto dfs, int now) -> int {
        vector<int> buka;
        for (auto v : graph[now]) {
            buka.push_back(dfs(dfs, v));
        }
        int tmp = 0;
        if (buka.size() == 0) {
            tmp = 1;
        } else {
            tmp = *max_element(all(buka)) + *min_element(all(buka)) + 1;
        }
        ans[now] = tmp;
        return tmp;
    };

    // cerr << "start" << endl;
    cout << dfs(dfs, 0) << endl;
}
