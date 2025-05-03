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
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
    }
    bool ok = true;
    if (m != n) {
        ok = false;
    }
    vector<int> cnt(n, 0);
    for (int i = 0; i < m; i++) {
        cnt[a[i]]++;
        cnt[b[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (cnt[i] != 2) {
            ok = false;
        }
    }
    dsu uf(n);
    for (int i = 0; i < m; i++) {
        if (uf.same(a[i], b[i])) {
            if (i != m - 1) {
                ok = false;
            }
            break;
        }
        uf.merge(a[i], b[i]);
        if (i == m - 1) {
            ok = false;
        }
    }
    auto group = uf.groups();
    if (group.size() == 1 && group[0].size() == n && ok) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
