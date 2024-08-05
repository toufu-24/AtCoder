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
    vector<vector<int>> in(N, vector<int>(2));
    vector<vector<pair<int, int>>> ice(N);
    int maximum = 0;
    for (int i = 0; i < N; i++) {
        cin >> in[i][0] >> in[i][1];
        in[i][0]--;
        ice[in[i][0]].push_back({in[i][1], i});
    }
    for (int i = 0; i < N; i++) {
        RSORT(ice[i]);
    }
    vector<pair<int, int>> maxes;
    for (int i = 0; i < N; i++) {
        if (ice[i].size() == 0) {
            continue;
        }
        maxes.push_back({ice[i][0].first, i});
    }
    RSORT(maxes);

    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (ice[i].size() == 0) {
            continue;
        }
        // 同じ味と違う味の2通り
        if (maxes[0].second == i) {
            ans = max(ans, ice[i][0].first + maxes[1].first);
            if (ice[i].size() >= 2) {
                ans = max(ans, ice[i][0].first + ice[i][1].first / 2);
            }
        } else {
            ans = max(ans, ice[i][0].first + maxes[0].first);
            if (ice[i].size() >= 2) {
                ans = max(ans, ice[i][0].first + ice[i][1].first / 2);
            }
        }
    }
    cout << ans << endl;
}
