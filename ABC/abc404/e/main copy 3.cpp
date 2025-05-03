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
    vector<int> c(n, -1), a(n, 0);
    for (int i = 1; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> a[i];
    }
    vector<int> now_arr(n, 0);
    now_arr[0] = reduce(all(a), 0);
    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        int nokori = now_arr[i];
        if (nokori == a[i]) {
            continue;
        }
        nokori -= a[i];
        if (nokori < 0) {
            assert(false);
        }
        if (nokori == 0) {
            continue;
        }
        ans++;
        int max_idx = -1;
        int max_idx_next = -1;
        for (int j = 0; j < n; j++) {
        }
    }
}
