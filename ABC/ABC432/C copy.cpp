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
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int sum = reduce(all(a));
    int left = 0, right = 1e18;
    while (abs(left - right) > 0) {
        int mid = (left + right) / 2;
        // mid個 大きいの配る
        int big = mid;
        int small = sum - big;
        if (small < 0) {
            right = mid;
            continue;
        }
        int sum_g = big * x + small * y;
        if(sum)
        bool ok = true;
    }
}
