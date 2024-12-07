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
    int h, w, d;
    cin >> h >> w >> d;
    vector<string> s(h);
    vector<pair<int, int>> floor;
    for (int i = 0; i < h; i++) {
        cin >> s[i];
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '.') {
                floor.push_back({i, j});
            }
        }
    }
    int n = floor.size();
    auto howmany = [&](int i, int j) -> int {
        auto s_tmp = s;
        auto one = floor[i];
        auto two = floor[j];
        // マンハッタン距離がd以下の床を探す
        set<pair<int, int>> near;
        for (int k = 0; k < n; k++) {
            if (abs(one.first - floor[k].first) + abs(one.second - floor[k].second) <= d) {
                near.insert(floor[k]);
            }
        }
        for (int k = 0; k < n; k++) {
            if (abs(two.first - floor[k].first) + abs(two.second - floor[k].second) <= d) {
                near.insert(floor[k]);
            }
        }
        return near.size();
    };
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = max(ans, howmany(i, j));
        }
    }
    cout << ans << endl;
}
