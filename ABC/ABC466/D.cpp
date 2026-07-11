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
    vector<int> r(m), c(m);
    for (int i = 0; i < m; i++) {
        cin >> r[i] >> c[i];
    }

    int ans = 0;
    set<int> bancol, banrow;
    for (int i = m - 1; i >= 0; i--) {
        if (banrow.contains(r[i]) || bancol.contains(c[i])) {
        } else {
            ans++;
        }

        banrow.insert(r[i]);
        bancol.insert(c[i]);
    }
    cout << ans << endl;
}
