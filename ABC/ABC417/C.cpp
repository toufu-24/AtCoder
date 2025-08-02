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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> plus(n), minus(n);
    for (int i = 0; i < n; i++) {
        plus[i] = a[i] + i;
        minus[i] = i - a[i];
    }
    SORT(plus);
    SORT(minus);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int up = upper_bound(all(minus), plus[i]) - minus.begin();
        int down = lower_bound(all(minus), plus[i]) - minus.begin();
        ans += up - down;
    }
    cout << ans << endl;
}
