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

struct pair_modint {
    modint a, b;
    pair_modint(modint aa, modint bb) : a(aa), b(bb) {}
    bool operator<(const pair_modint &other) const {
        if (a != other.a)
            return a.val() < other.a.val();
        return b.val() < other.b.val();
    }
};

int32_t main() {
    int n, m;
    cin >> n >> m;
    modint::set_mod(n);
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
    }

    set<pair_modint> lines;
    for (int i = 0; i < m; i++) {
        if (a[i] > b[i]) {
            swap(a[i], b[i]);
        }
        lines.insert({a[i], b[i]});
        lines.insert({b[i], a[i]});
    }

    set<pair<pair_modint, pair_modint>> used;
    int ans = m * (m - 1) / 2;
    // 平行なら交わらない
    for (const auto &[aa, bb] : lines) {
        auto tmp_a = aa, tmp_b = bb;
        auto prev_tmp_a = aa, prev_tmp_b = bb;
        // 時計回り方向の探索
        while (prev_tmp_a != tmp_b && tmp_b != tmp_a) {
            if (lines.count({tmp_a, tmp_b})) {
                if (aa.val() == tmp_a.val() && bb.val() == tmp_b.val()) {
                    // 同じ直線の場合は何もしない
                } else {
                    if (!used.count({{aa, bb}, {tmp_a, tmp_b}})) {
                        ans--;
                    }
                    used.insert({{aa, bb}, {tmp_a, tmp_b}});
                    used.insert({{tmp_a, tmp_b}, {aa, bb}});
                    used.insert({{bb, aa}, {tmp_b, tmp_a}});
                    used.insert({{tmp_b, tmp_a}, {bb, aa}});
                }
            }
            prev_tmp_a = tmp_a;
            prev_tmp_b = tmp_b;
            tmp_a++;
            tmp_b--;
        }
        tmp_a = aa, tmp_b = bb;
        prev_tmp_a = aa, prev_tmp_b = bb;
        // 反時計回り方向の探索
        while (prev_tmp_a != tmp_b && tmp_b != tmp_a) {
            if (lines.count({tmp_a, tmp_b})) {
                if (aa.val() == tmp_a.val() && bb.val() == tmp_b.val()) {
                    // 同じ直線の場合は何もしない
                } else {
                    if (!used.count({{aa, bb}, {tmp_a, tmp_b}})) {
                        ans--;
                    }
                    used.insert({{aa, bb}, {tmp_a, tmp_b}});
                    used.insert({{tmp_a, tmp_b}, {aa, bb}});
                    used.insert({{bb, aa}, {tmp_b, tmp_a}});
                    used.insert({{tmp_b, tmp_a}, {bb, aa}});
                }
            }
            prev_tmp_a = tmp_a;
            prev_tmp_b = tmp_b;
            tmp_a--;
            tmp_b++;
        }
    }
    cout << ans << endl;
}
