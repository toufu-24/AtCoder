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
    vector<pair<int, int>> ab(n), cd(m);
    for (int i = 0; i < n; i++) {
        cin >> ab[i].first >> ab[i].second;
    }
    for (int i = 0; i < m; i++) {
        cin >> cd[i].first >> cd[i].second;
    }

    for (int i = 0; i < n; i++) {
        int min_dist = 1e18;
        int ans = -1;
        for (int j = 0; j < m; j++) {
            int dist = abs(ab[i].first - cd[j].first) + abs(ab[i].second - cd[j].second);
            if (dist < min_dist) {
                ans = j + 1;
                min_dist = dist;
            }
        }
        cout << ans << endl;
    }
}
