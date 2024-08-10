#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
    int N, D;
    cin >> N >> D;
    vector<pair<int, int>> xy(N);
    vector<int> x_arr(N), y_arr(N);
    for (int i = 0; i < N; i++) {
        cin >> xy[i].first >> xy[i].second;
        x_arr[i] = xy[i].first;
        y_arr[i] = xy[i].second;
    }
    SORT(x_arr), SORT(y_arr);
    vector<int> x_sum(N + 1, 0), y_sum(N + 1, 0);
    for (int i = 0; i < N; i++) {
        x_sum[i + 1] = x_sum[i] + x_arr[i];
        y_sum[i + 1] = y_sum[i] + y_arr[i];
    }

    int ans = 0;
    for (int x = -2e6 - 1; x <= 2e6 + 1; x++) {
        // このx座標で条件を満たすy座標が何個あるか
        // 二分探索
        // 上限の探索
        int upper = 2e6 + 1;
        int lower = -2e6 - 1;
        while (abs(upper - lower) > 1) {
            int mid = (upper + lower) / 2;
            // {x,mid} からの距離がD以下になるような点の数を数える
            int xdist = 0, ydist = 0;
            // x
            int x_idx = lower_bound(all(x_arr), x) - x_arr.begin();
            xdist = x_sum[N] - x_sum[x_idx] - x_sum[x_idx] - x * (N - x_idx) + x * x_idx;
            // y
            int y_idx = lower_bound(all(y_arr), mid) - y_arr.begin();
            ydist = y_sum[N] - y_sum[y_idx] - y_sum[y_idx] - mid * (N - y_idx) + mid * y_idx;

            int dist = xdist + ydist;
            if (dist > D) {
                upper = mid;
            } else {
                lower = mid;
            }
        }

        // 下限の探索
        int upper2 = 2e6 + 1;
        int lower2 = -2e6 - 1;
        while (abs(upper2 - lower2) > 1) {
            int mid = (upper2 + lower2) / 2;
            // {x,mid} からの距離がD以下になるような点の数を数える
            int xdist = 0, ydist = 0;
            // x
            int x_idx = lower_bound(all(x_arr), x) - x_arr.begin();
            xdist = x_sum[N] - x_sum[x_idx] - x_sum[x_idx] - x * (N - x_idx) + x * x_idx;
            // y
            int y_idx = lower_bound(all(y_arr), mid) - y_arr.begin();
            ydist = y_sum[N] - y_sum[y_idx] - y_sum[y_idx] - mid * (N - y_idx) + mid * y_idx;

            int dist = xdist + ydist;
            if (dist > D) {
                lower2 = mid;
            } else {
                upper2 = mid;
            }
        }
        if (upper < upper2)
            continue;
        ans += upper - upper2;
    }
    cout << ans << endl;
}
