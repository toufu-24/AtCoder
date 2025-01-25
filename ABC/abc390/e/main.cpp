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
    int n, x;
    cin >> n >> x;
    vector<int> v(n), a(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i] >> a[i] >> c[i];
    }
    vector<tuple<int, int, int>> ones, twos, threes;
    for (int i = 0; i < n; i++) {
        if (v[i] == 1) {
            ones.push_back({v[i], a[i], c[i]});
        } else if (v[i] == 2) {
            twos.push_back({v[i], a[i], c[i]});
        } else {
            threes.push_back({v[i], a[i], c[i]});
        }
    }
    sort(all(ones), [](tuple<int, int, int> a, tuple<int, int, int> b) {
        return get<2>(a) < get<2>(b);
    });
    sort(all(twos), [](tuple<int, int, int> a, tuple<int, int, int> b) {
        return get<2>(a) < get<2>(b);
    });
    sort(all(threes), [](tuple<int, int, int> a, tuple<int, int, int> b) {
        return get<2>(a) < get<2>(b);
    });
}
