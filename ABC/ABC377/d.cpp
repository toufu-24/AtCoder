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
    vector<int> L(n), R(n);
    vector<pair<int, int>> LR(n);
    for (int i = 0; i < n; i++) {
        cin >> L[i] >> R[i];
        L[i]--;
        R[i]--;
        LR[i] = {L[i], R[i]};
    }
    SORT(LR);
    L.push_back(m);
    R.push_back(m);
    n++;
    vector<int> sorted_L = L, sorted_R = R;
    SORT(sorted_L);
    SORT(sorted_R);
    vector<int> min_R(n);
    min_R[n - 1] = R[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        min_R[i] = min(min_R[i + 1], LR[i].second);
    }
    int ans = 0;
    for (int l = 0; l <= m; l++) {
        // l以上のLで最小のRを求める
        int idx = lower_bound(all(sorted_L), l) - sorted_L.begin();
        if (idx == n) {
            continue;
        }
        int r = min_R[idx];
        int add = r - l;
        ans += add;
    }

    cout << ans << endl;
}
