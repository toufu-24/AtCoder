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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> cost1(n, 0), cost0(n, 0);
        for (int i = 0; i < n; i++) {
            cost1[i] = (s[i] == '0');
            cost0[i] = (s[i] == '1');
        }
        // 左からそれにするコスト
        vector<int> sum1(n + 1, 0), sum0(n + 1, 0);
        for (int i = 0; i < n; i++) {
            sum1[i + 1] = sum1[i] + cost1[i];
            sum0[i + 1] = sum0[i] + cost0[i];
        }
        // 右からそれにするコスト
        vector<int> sum1_rev(n + 1, 0), sum0_rev(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            sum1_rev[i] = sum1_rev[i + 1] + cost1[i];
            sum0_rev[i] = sum0_rev[i + 1] + cost0[i];
        }
        int ans = LLONG_MAX;
        // for (int i = 0; i <= n; i++) {
        //     for (int j = i; j <= n; j++) {
        //         ans = min(ans, sum0[i] + sum0_rev[j] + (sum1[j] - sum1[i]));
        //     }
        // }
        vector<int> i_array(n + 1, 0), j_array(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            i_array[i] = sum0[i] - sum1[i];
            j_array[i] = sum0_rev[i] + sum1[i];
        }
        int min_left = 1e18;
        for (int i = 0; i <= n; i++) {
            min_left = min(min_left, i_array[i]);
            ans = min(ans, min_left + j_array[i]);
        }
        cout << ans << endl;
    }
}
