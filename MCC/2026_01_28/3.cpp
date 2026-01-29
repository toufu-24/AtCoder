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
    int k;
    cin >> k;
    vector<vector<int>> cd(k, vector<int>(2));
    vector<int> c(k), d(k);
    for (int i = 0; i < k; i++) {
        cin >> c[i] >> d[i];
        c[i]--, d[i]--;
        cd[i][0] = c[i];
        cd[i][1] = d[i];
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << k); mask++) {
        vector<int> dish(n, 0);
        for (int i = 0; i < k; i++) {
            dish[cd[i][(mask >> i) & 1]]++;
        }

        int ok = 0;
        for (int i = 0; i < m; i++) {
            assert((dish[a[i]] && dish[b[i]]) <= 1);
            ok += (dish[a[i]] && dish[b[i]]);
        }
        ans = max(ans, ok);
    }
    cout << ans << endl;
}
