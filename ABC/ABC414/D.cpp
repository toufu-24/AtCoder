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
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    SORT(x);
    vector<pair<int, int>> interval(n - 1);
    for (int i = 0; i < n - 1; i++) {
        interval[i] = {x[i + 1] - x[i], i};
    }
    SORT(interval);
    set<int> kesu;
    for (int i = 0; i < m - 1; i++) {
        kesu.insert(interval.back().second);
        interval.pop_back();
    }
    vector<vector<int>> group(m);
    int idx = 0;
    for (int i = 0; i < n; i++) {
        group[idx].push_back(x[i]);
        if (kesu.contains(i)) {
            idx++;
            assert(idx < m);
        }
    }

    for (int i = 0; i < m; i++) {
        SORT(group[i]);
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
        ans += group[i].back() - group[i].front();
    }
    cout << ans << endl;
}
