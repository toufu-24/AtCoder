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
    dsu nibuhan(n + 2); // n -> white, n+1 -> black
    dsu d(n);
    bool not_2 = false;
    int ans = 0;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (nibuhan.same(u, n) && nibuhan.same(v, n)) {
            not_2 = true;
        }
        if (nibuhan.same(u, n + 1) && nibuhan.same(v, n + 1)) {
            not_2 = true;
        }
        if (not_2) {
            cout << -1 << endl;
            continue;
        }
        // uをwhite, vをblackにする
        if (nibuhan.same(u, n + 1)) {
            swap(u, v);
        }
        assert(!nibuhan.same(u, n + 1));
        assert(!nibuhan.same(v, n));
        nibuhan.merge(u, n);
        nibuhan.merge(v, n + 1);

        if (!d.same(u, v)) {
            int pre_u_size = d.size(u);
            int pre_v_size = d.size(v);
            d.merge(u, v);
            int next_u_size = d.size(u);
            ans -= pre_u_size / 2;
            ans -= pre_v_size / 2;
            ans += next_u_size / 2;
        }
        cout << ans << endl;
    }
}
