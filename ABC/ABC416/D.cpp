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
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i] %= m;
        }
        SORT(a);
        vector<int> b(n);
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            b[i] %= m;
        }
        SORT(b);
        map<int, int> mpb;
        for (int i = 0; i < n; i++) {
            mpb[b[i]]++;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int nokori = m - a[i];
            auto it = mpb.lower_bound(nokori);
            if (it == mpb.end()) {
                it = mpb.begin();
            }
            ans += (a[i] + it->first) % m;
            mpb[it->first]--;
            if (mpb[it->first] == 0) {
                mpb.erase(it->first);
            }
        }
        cout << ans << endl;
    }
}
