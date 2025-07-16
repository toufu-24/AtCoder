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
    vector<int> l(n), r(n);
    vector<pair<int, int>> interval(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        interval[i] = {l[i], r[i]};
    }
    SORT(interval);
    int now_l = interval[0].first, now_r = interval[0].second;
    for (int i = 1; i < n; i++) {
        if (interval[i].first > now_r) {
            cout << now_l << " " << now_r << endl;
            now_l = interval[i].first;
            now_r = interval[i].second;
        } else {
            now_r = max(now_r, interval[i].second);
        }
    }
    cout << now_l << " " << now_r << endl;
}
