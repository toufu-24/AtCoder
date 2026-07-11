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
    vector<int> a(n + 2);
    a[0] = 0;
    a[n + 1] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    int now = 0;
    for (int i = 0; i < n + 2; i++) {
        ans += abs(a[i] - now);
        now = a[i];
    }

    for (int i = 1; i <= n; i++) {
        cout << ans - abs(a[i] - a[i - 1]) - abs(a[i] - a[i + 1]) + abs(a[i - 1] - a[i + 1]) << endl;
    }
}
