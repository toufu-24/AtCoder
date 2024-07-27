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
    int N, Q;
    cin >> N >> Q;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        a[i] += 1e8;
    }
    SORT(a);
    vector<pair<int, int>> queries(Q);
    for (int i = 0; i < Q; i++) {
        cin >> queries[i].first >> queries[i].second;
        queries[i].first += 1e8;
    }

    for (int q = 0; q < Q; q++) {
        int b = queries[q].first, k = queries[q].second;
        k--;
        // 左を二分探索
        int b_idx = upper_bound(all(a), b) - a.begin();
        int left = 0, right = b_idx;
        while (right - left > 1) {
            int mid = (left + right) / 2;
            if (mid + k < N) {
                int mid_left = abs(a[mid] - b);
                int mid_right = abs(a[mid + k] - b);
                if (mid_right - mid_left > 0) {
                    right = mid;
                } else {
                    left = mid;
                }
            } else {
                right = mid;
            }
        }
        int ans = 1e18;
        if (left + k < N)
            ans = max(abs(a[left] - b), abs(a[left + k] - b));
        if (right + k < N)
            ans = min(ans, max(abs(a[right] - b), abs(a[right + k] - b)));
        cout << ans << endl;
    }
}
