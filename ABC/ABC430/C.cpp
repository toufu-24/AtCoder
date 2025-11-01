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
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;

    vector<int> a_sum(n + 1, 0), b_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        a_sum[i + 1] = a_sum[i] + (s[i] == 'a');
        b_sum[i + 1] = b_sum[i] + (s[i] == 'b');
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a_idx = lower_bound(all(a_sum), a + a_sum[i]) - a_sum.begin(); // A以上になる最小
        int b_idx = lower_bound(all(b_sum), b + b_sum[i]) - b_sum.begin(); // B以上になる最小

        ans += max(b_idx - a_idx, 0L);
    }
    cout << ans << endl;
}
