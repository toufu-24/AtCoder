#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

// #define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main() {
    int n, m;
    cin >> n >> m;
    set<int> kesshou;
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        kesshou.insert(a[i]);
        kesshou.insert(b[i]);
    }

    int ans = 0;
    set<pair<int, int>> wins;
    //  全部にいるパターン
    set<int> all;
    for (int i = 0; i < 2; i++) {
        int now = (i == 0) ? a[0] : b[0];

        // all nowも注意
        // now == kouhoがだめ
        int kouho = -1;
        for (int j = 0; j < m; j++) {
            set<int> t = {a[j], b[j]};
            if (t.contains(now)) {
                continue;
            }
            kouho = now + 1;
            break;
        }
        assert(now != kouho);
        if (kouho == -1) {
            all.insert(now);
            // 他の全部OK
            if (all.size() != 1) {
                ans += n - kesshou.size();
                continue;
            }
            ans += n - 1;
            // wins.insert({now, -1});
        }
    }

    for (int i = 0; i < 2; i++) {
        int now = (i == 0) ? a[0] : b[0];
        if (all.contains(now)) {
            continue;
        }

        for (int k = 0; k < 2; k++) {
            // all nowも注意
            // now == kouhoがだめ
            int kouho = -1;
            for (int j = 0; j < m; j++) {
                set<int> t = {a[j], b[j]};
                if (t.contains(now)) {
                    continue;
                }
                kouho = (k == 0) ? a[j] : b[j];
                break;
            }
            assert(now != kouho);
            assert(kouho != -1);
            if (all.contains(kouho)) {
                continue;
            }

            bool ok = true;
            for (int j = 0; j < m; j++) {
                set<int> t = {a[j], b[j]};
                if (t.contains(now) || t.contains(kouho)) {
                    continue;
                } else {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                assert(kesshou.contains(kouho));
                assert(kesshou.contains(now));
                if (kouho < now) {
                    wins.insert({kouho, now});
                } else {
                    wins.insert({now, kouho});
                }
            }
        }
    }

    cout << ans + wins.size() << endl;
}
