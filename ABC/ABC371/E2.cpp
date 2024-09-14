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

set<int> op(set<int> a, set<int> b) {
    for (int x : b) {
        a.insert(x);
    }
    return a;
}

set<int> e() {
    return set<int>();
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<set<int>> inist(n);
    for (int i = 0; i < n; i++) {
        inist[i].insert(a[i]);
    }
    segtree<set<int>, op, e> seg(inist);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ans += seg.prod(i, j + 1).size();
        }
    }
    cout << ans << endl;
}
