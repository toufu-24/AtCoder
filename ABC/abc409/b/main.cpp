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
    SORT(a);
    int l = 0, r = 1e9 + 1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] >= mid) {
                cnt++;
            }
        }
        if (cnt >= mid) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << endl;
}
