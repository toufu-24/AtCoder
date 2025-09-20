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
    vector<int> a(n), b(n);
    vector<vector<int>> graph(n + 1);

    queue<int> q;
    set<int> ans;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        if (a[i] == 0 && b[i] == 0) {
            q.push(i + 1);
        }
        graph[a[i]].push_back(i + 1);
        graph[b[i]].push_back(i + 1);
    }

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        ans.insert(now);
        for (auto next : graph[now]) {
            if (!ans.contains(next)) {
                ans.insert(next);
                q.push(next);
            }
        }
    }
    cout << ans.size() << endl;
}
