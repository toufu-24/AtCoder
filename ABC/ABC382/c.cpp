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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    vector<int> arr(n + 1, 1e9);
    for (int i = 0; i < n; i++) {
        arr[i + 1] = min(a[i], arr[i]);
    }
    REVERSE(arr);
    for (int i = 0; i < m; i++) {
        int idx = upper_bound(all(arr), b[i]) - arr.begin();
        idx--;
        if (n - idx == n + 1) {
            cout << -1 << endl;
            continue;
        }
        cout << n - idx << endl;
    }
}
