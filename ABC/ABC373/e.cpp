// 候補者は，その候補者より多く票を獲得した候補者がM人未満であるとき当選します．各候補者が当選を確定させるためには最小で何票必要か求めてください．ただし，そのような票数が存在しない場合は-1を出力してください．

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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> sorted_a = a;
    SORT(sorted_a);
    int remain = k;
    for (int i = 0; i < n; i++) {
        remain -= a[i];
    }

    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        mp[a[i]]++;
    }

    vector<int> diff_sum(n, 0);
    for (int i = 0; i < n - 1; i++) {
        diff_sum[i + 1] = diff_sum[i] + a[i + 1] - a[i];
    }

    for (int i = 0; i < n; i++) {
        int max_get = a[i] + remain;
        int max_get_idx = upper_bound(all(sorted_a), max_get) - sorted_a.begin();
        max_get_idx--;
        int max_get_upper = n - max_get_idx;
        if (max_get_upper > m) {
            cout << -1 << " ";
            continue;
        }

        // 何票で確定か
        int m_th_val = sorted_a[n - m];
        int winner_idx = lower_bound(all(sorted_a), m_th_val) - sorted_a.begin();
        int ans = 0;
        if (m_th_val <= a[i]) {
            // 自分が当選者に含まれる
            // winner_idx-1 ~ n-1 と勝負
            int left = winner_idx - 1;
            int right = n;
            while (left < right) {
                int mid = (left + right) / 2;
                if ((diff_sum[mid + 1] - diff_sum[winner_idx - 1]) * (mid - (winner_idx - 1)) <= remain) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            ans += sorted_a[left] + 1 - a[i];
        } else {
            // 自分が当選者に含まれない
            // winner_idx-1 ~ n-1 と勝負
            int left = winner_idx - 1;
            int right = n;
            while (left < right) {
                int mid = (left + right) / 2;
                if ((diff_sum[mid + 1] - diff_sum[winner_idx - 1]) * (mid - (winner_idx - 1)) <= remain) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            ans += sorted_a[left] + 1 - a[i];
        }
        cout << ans << " ";
    }
    cout << endl;
}
