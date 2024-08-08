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
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    vector<int> a(M), b(M);
    for (int i = 0; i < M; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
        G[a[i]].push_back(b[i]);
        G[b[i]].push_back(a[i]);
    }

    int ans = 0;
    queue<vector<int>> q;
    q.push({0});
    while (!q.empty()) {
        vector<int> path = q.front();
        int now = path.back();
        q.pop();
        for (auto next : G[now]) {
            if (find(all(path), next) != path.end()) {
                continue;
            }
            vector<int> next_path = path;
            next_path.push_back(next);
            if (next_path.size() == N) {
                ans++;
                continue;
            }
            q.push(next_path);
        }
    }

    cout << ans << endl;
}
