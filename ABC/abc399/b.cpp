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
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    int r = 1;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = {p[i], i};
    }
    RSORT(v);
    int prev = v[0].first;
    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++) {
        if (v[i].first == prev) {
            ans[v[i].second] = r;
        } else {
            r = i + 1;
            ans[v[i].second] = r;
            prev = v[i].first;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i];
        cout << endl;
    }
}
