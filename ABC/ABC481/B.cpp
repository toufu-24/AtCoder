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
    int n, k;
    cin >> n >> k;

    int ans = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == k) {
            ans++;
        }
    }
    for (int i = 1; i < n; i++) {
        int t = a[i - 1], tt = a[i];
        if (t > tt) {
            swap(t, tt);
        }
        if (t < k && k < tt) {
            ans++;
        }
    }
    cout << ans << endl;
}
