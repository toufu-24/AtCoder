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
constexpr int n = 1000;
void output(vector<ans_data> &ans) {
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].before_x << " " << ans[i].before_y << " " << ans[i].after_x << " " << ans[i].after_y << endl;
    }
}

pair<int, vector<ans_data>> execute(vector<pair<int, int>> a_b) {
    int cost = 0;
    int limit = n * 5;
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
        cost += xDiff + yDiff;
        pair<int, int> prev_added = min_diff_pair;
        int insert = 5;
        if (i < 2) {
            insert = 15;
        }
        if (limit - insert < n - i) {
            insert = 1;
            // cerr << "limit" << endl;
        }
        limit -= insert;
        for (int j = 1; j <= insert - 1; j++) {
            pair<int, int> next_added = {min_diff_pair.first + j * xDiff / insert, min_diff_pair.second + j * yDiff / insert};
            ans.push_back({prev_added.first, prev_added.second, next_added.first, next_added.second});
            already_made.push_back(next_added);
            prev_added = next_added;
        }
        ans.push_back({prev_added.first, prev_added.second, want_make.first, want_make.second});
        already_made.push_back(want_make);
    }
    return {cost, ans};
}

int32_t main() {
    ld start = clock();
    constexpr ld TIME_LIMIT = 1.9 * CLOCKS_PER_SEC;
    int _n;
    cin >> _n;
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
    // 0を要素に持つ奴を先頭に持ってくる
    for (int i = 0; i < n; i++) {
        if (a_b[i].first == 0 || a_b[i].second == 0) {
            auto tmp = a_b[i];
            a_b.erase(a_b.begin() + i);
            a_b.insert(a_b.begin(), tmp);
        }
    }

    auto [cost, ans] = execute(a_b);
    ld end = clock();
    random_device seed_gen;
    mt19937 engine(seed_gen());
    int cnt = 0;
    while (end - start < TIME_LIMIT / 6) {
        cnt++;
        int idx1 = uniform_int_distribution<int>(0, n / 6 - 1)(engine);
        int idx2 = uniform_int_distribution<int>(0, n / 6 - 1)(engine);
        swap(a_b[idx1], a_b[idx2]);
        auto [new_cost, new_ans] = execute(a_b);
        if (new_cost < cost) {
            cost = new_cost;
            ans = new_ans;
        } else {
            swap(a_b[idx1], a_b[idx2]);
        }
        end = clock();
    }
    while (end - start < TIME_LIMIT * 2 / 6) {
        cnt++;
        int idx3 = uniform_int_distribution<int>(n / 6, n / 3 - 1)(engine);
        int idx4 = uniform_int_distribution<int>(n / 6, n / 3 - 1)(engine);
        swap(a_b[idx3], a_b[idx4]);
        auto [new_cost, new_ans] = execute(a_b);
        if (new_cost < cost) {
            cost = new_cost;
            ans = new_ans;
        } else {
            swap(a_b[idx3], a_b[idx4]);
        }
        end = clock();
    }
    while (end - start < TIME_LIMIT * 3 / 6) {
        cnt++;
        int idx1 = uniform_int_distribution<int>(n / 3, n / 2 - 1)(engine);
        int idx2 = uniform_int_distribution<int>(n / 3, n / 2 - 1)(engine);
        swap(a_b[idx1], a_b[idx2]);
        auto [new_cost, new_ans] = execute(a_b);
        if (new_cost < cost) {
            cost = new_cost;
            ans = new_ans;
        } else {
            swap(a_b[idx1], a_b[idx2]);
        }
        end = clock();
    }
    while (end - start < TIME_LIMIT * 4 / 6) {
        cnt++;
        int idx3 = uniform_int_distribution<int>(n / 2, 2 * n / 3 - 1)(engine);
        int idx4 = uniform_int_distribution<int>(n / 2, 2 * n / 3 - 1)(engine);
        swap(a_b[idx3], a_b[idx4]);
        auto [new_cost, new_ans] = execute(a_b);
        if (new_cost < cost) {
            cost = new_cost;
            ans = new_ans;
        } else {
            swap(a_b[idx3], a_b[idx4]);
        }
        end = clock();
    }
    while (end - start < TIME_LIMIT * 5 / 6) {
        cnt++;
        int idx1 = uniform_int_distribution<int>(2 * n / 3, 5 * n / 6 - 1)(engine);
        int idx2 = uniform_int_distribution<int>(2 * n / 3, 5 * n / 6 - 1)(engine);
        swap(a_b[idx1], a_b[idx2]);
        auto [new_cost, new_ans] = execute(a_b);
        if (new_cost < cost) {
            cost = new_cost;
            ans = new_ans;
        } else {
            swap(a_b[idx1], a_b[idx2]);
        }
        end = clock();
    }
    while (end - start < TIME_LIMIT) {
        cnt++;
        int idx3 = uniform_int_distribution<int>(5 * n / 6, n - 1)(engine);
        int idx4 = uniform_int_distribution<int>(5 * n / 6, n - 1)(engine);
        swap(a_b[idx3], a_b[idx4]);
        auto [new_cost, new_ans] = execute(a_b);
        if (new_cost < cost) {
            cost = new_cost;
            ans = new_ans;
        } else {
            swap(a_b[idx3], a_b[idx4]);
        }
        end = clock();
    }
    output(ans);
    cerr << "cnt: " << cnt << endl;
}
