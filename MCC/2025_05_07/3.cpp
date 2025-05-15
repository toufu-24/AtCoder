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
    int n, x;
    cin >> n >> x;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<int> sum(n, 0);
    sum[0] = a[0] + b[0];
    for (int i = 1; i < n; i++) {
        sum[i] = a[i] + b[i] + sum[i - 1];
    }

    int ans = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        if (i >= x) {
            continue;
        }
        int tmp = 0, cnt = 0;
        tmp += sum[i];
        cnt += i + 1;
        tmp += (x - cnt) * b[i];
        ans = min(ans, tmp);
    }
    cout << ans << endl;
}
