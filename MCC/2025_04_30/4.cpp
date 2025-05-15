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

int pow2(int x) {
    return x * x;
}

int32_t main() {
    int n;
    cin >> n;
    pair<int, int> start, goal;
    cin >> start.first >> start.second >> goal.first >> goal.second;
    vector<tuple<int, int, int>> cirles(n);
    for (int i = 0; i < n; i++) {
        cin >> get<0>(cirles[i]) >> get<1>(cirles[i]) >> get<2>(cirles[i]);
    }
    int st_idx = -1, goal_idx = -1;
    for (int i = 0; i < n; i++) {
        auto [x, y, r] = cirles[i];
        if (pow2(x - start.first) + pow2(y - start.second) == pow2(r)) {
            st_idx = i;
            cerr << "st_idx: " << st_idx << endl;
        }
        if (pow2(x - goal.first) + pow2(y - goal.second) == pow2(r)) {
            goal_idx = i;
            cerr << "goal_idx: " << goal_idx << endl;
        }
    }
    if (st_idx == -1 || goal_idx == -1) {
        cerr << "not found" << endl;
        cerr << st_idx << " " << goal_idx << endl;
        return 1;
    }
    dsu uf(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto [x1, y1, r1] = cirles[i];
            auto [x2, y2, r2] = cirles[j];
            if (pow2(x1 - x2) + pow2(y1 - y2) < pow2(r1 - r2)) {
                continue;
            }
            if (pow2(x1 - x2) + pow2(y1 - y2) <= pow2(r1 + r2)) {
                uf.merge(i, j);
            }
        }
    }

    if (uf.same(st_idx, goal_idx)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
