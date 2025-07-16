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
    int n;
    cin >> n;
    vector<int> a(n), a2(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a2[i];
    }

    int ans = 0;
    vector<int> sum_a(n + 1, 0), sum_a2(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sum_a[i + 1] = sum_a[i] + a[i];
        sum_a2[i + 1] = sum_a2[i] + a2[i];
    }

    for (int i = 0; i < n; i++) {
        ans = max(ans, sum_a[i] + sum_a2[n] - sum_a2[i] + a[i]);
    }
    cout << ans << endl;
}
