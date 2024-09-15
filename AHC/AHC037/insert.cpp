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

struct ans_data {
    int before_x, before_y;
    int after_x, after_y;
};
void output(vector<ans_data> &ans) {
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].before_x << " " << ans[i].before_y << " " << ans[i].after_x << " " << ans[i].after_y << endl;
    }
}

int32_t main() {
    int _n;
    cin >> _n;
    constexpr int n = 1000;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<pair<int, int>> a_b(n);
    for (int i = 0; i < n; i++) {
        a_b[i] = {a[i], b[i]};
    }
    sort(all(a_b), [](pair<int, int> x, pair<int, int> y) {
        return x.first + x.second < y.first + y.second;
    });

    vector<pair<int, int>> already_made;
    already_made.push_back({0, 0});

    vector<ans_data> ans;
    for (int i = 0; i < n; i++) {
        auto want_make = a_b[i];
        // already_madeの中で，want_makeよりもfirstもsecondも小さいものから選ぶ
        int min_diff = 1e18;
        pair<int, int> min_diff_pair = {0, 0};
        for (int j = 0; j < already_made.size(); j++) {
            auto made = already_made[j];
            if (made.first > want_make.first || made.second > want_make.second) {
                continue;
            }
            int diff = abs(made.first - want_make.first) + abs(made.second - want_make.second);
            if (diff < min_diff) {
                min_diff = diff;
                min_diff_pair = made;
            }
        }
        // want_makeとmin_diff_pairの間に等間隔に4つの座標を追加
        int xDiff = want_make.first - min_diff_pair.first, yDiff = want_make.second - min_diff_pair.second;
        pair<int, int> prev_added = min_diff_pair;
        for (int j = 1; j <= 4; j++) {
            pair<int, int> next_added = {min_diff_pair.first + j * xDiff / 5, min_diff_pair.second + j * yDiff / 5};
            ans.push_back({prev_added.first, prev_added.second, next_added.first, next_added.second});
            already_made.push_back(next_added);
            prev_added = next_added;
        }
        ans.push_back({prev_added.first, prev_added.second, want_make.first, want_make.second});
        already_made.push_back(want_make);
    }

    output(ans);
}
