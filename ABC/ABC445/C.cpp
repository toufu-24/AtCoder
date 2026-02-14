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
    map<int, vector<int>> mp;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        mp[a[i]].push_back(i);
    }

    vector<int> ans(n);
    set<int> seen;
    for (int i = n - 1; i >= 0; i--) {
        if (seen.contains(i)) {
            continue;
        }
        queue<int> que;
        que.push(i);
        ans[i] = i;
        seen.insert(i);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (auto next : mp[v]) {
                if (seen.contains(next)) {
                    continue;
                }
                ans[next] = i;
                que.push(next);
                seen.insert(next);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
}
