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
    int n, q;
    cin >> n >> q;
    vector<int> cnt(n, 1);
    vector<int> bird(n, 0);
    iota(all(bird), 0);
    int ans = 0;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int p, h;
            cin >> p >> h;
            p--;
            h--;
            if (cnt[bird[p]] == 2) {
                ans--;
            }
            cnt[bird[p]]--;
            if (cnt[h] == 1) {
                ans++;
            }
            cnt[h]++;
            bird[p] = h;
        } else {
            cout << ans << endl;
        }
    }
}
