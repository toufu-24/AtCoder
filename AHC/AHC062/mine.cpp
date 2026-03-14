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

constexpr int TIME_LIMIT = 2800;

int32_t main() {
    auto start = chrono::high_resolution_clock::now();
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    int score = 0;
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans.push_back({i, j});
        }
    }

    auto calc_score = [&](vector<pair<int, int>> ans) {
        int score = 0;
        int idx = 0;
        for (auto [i, j] : ans) {
            score += a[i][j] * idx;
            idx++;
        }
        return score;
    };
    score = calc_score(ans);

    while (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() < TIME_LIMIT) {
        int i = rand() % (ans.size() - 1);
        swap(ans[i], ans[i + 1]);
        int new_score = calc_score(ans);
        if (new_score > score) {
            score = new_score;
        } else {
            swap(ans[i], ans[i + 1]);
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
}
