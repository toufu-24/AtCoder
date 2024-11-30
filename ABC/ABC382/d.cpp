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
    vector<vector<int>> ans;
    queue<vector<int>> q;
    for (int i = 1; i <= m; i++) {
        q.push({i});
    }
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        if (v.size() == n) {
            ans.push_back(v);
            continue;
        }
        int this_depth_max = m - (n - (v.size() + 1)) * 10;
        for (int i = 10; i <= m; i++) {
            int next = v.back() + i;
            if (next <= this_depth_max) {
                v.push_back(next);
                q.push(v);
                v.pop_back();
            } else {
                break;
            }
        }
    }

    cout << ans.size() << endl;
    for (auto v : ans) {
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << endl;
    }
}
