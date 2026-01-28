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
    vector<int> x(n), y(n);
    vector<int> shogen(n); // 数学通りではなく，右上から時計回り
    vector<ld> angle(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        if (x[i] >= 0 && y[i] >= 0) {
            shogen[i] = 1;
        } else if (x[i] >= 0 && y[i] <= 0) {
            shogen[i] = 2;
        } else if (x[i] <= 0 && y[i] <= 0) {
            shogen[i] = 3;
        } else {
            shogen[i] = 4;
        }
        angle[i] = atan2(y[i], x[i]);
    }
    vector<tuple<ld, int, int, int>> points;
    for (int i = 0; i < n; i++) {
        points.push_back({angle[i], x[i], y[i], i});
    }
    RSORT(points);
    auto po2 = points;
    for (int i = 0; i < n; i++) {
        points.push_back(po2[i]);
    }
    vector<ld> angle_srted;
    for (auto x : points) {
        angle_srted.push_back(-get<0>(x));
    }

    // cerr << "query" << endl;
    ld eps = 0;
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        // cerr << "input" << endl;
        // cerr << a << " " << b << endl;
        ld a_angle = -(angle[a] - eps);
        ld b_angle = -(angle[b] + eps);

        // cerr << "angle" << endl;
        auto a_idx = lower_bound(angle_srted.begin(), angle_srted.begin() + n, a_angle) - angle_srted.begin();
        auto b_idx = upper_bound(angle_srted.begin(), angle_srted.begin() + n, b_angle) - angle_srted.begin();
        // cerr << a_idx << " " << b_idx << endl;
        // cerr << "pre bound" << endl;
        if (a_idx >= b_idx) {
            b_idx = upper_bound(angle_srted.begin() + n, angle_srted.end(), b_angle) - angle_srted.begin();
        }
        // cerr << a_idx << " " << b_idx << endl;
        // cerr << "bound" << endl;
        cout << b_idx - a_idx << endl;
    }
}
