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
    vector<tuple<int, int, int>> xy(n);
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        xy[i] = {x[i], y[i], i};
    }
    SORT(xy);

    int ans = 0;
    set<int> yst;
    for (int i = 0; i < n; i++) {
        // xはそれ以下であるので，
        // yが現地点以下のが存在するか
        auto [nx, ny, ni] = xy[i];
        auto itr = yst.lower_bound(ny);
        if (itr == yst.begin()) {
            ans++;
        }
        yst.insert(ny);
    }

    cout << ans << endl;
}
