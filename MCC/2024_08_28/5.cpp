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
    modint::set_mod(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int sum = reduce(all(a));
    sort(all(a), [&](int x, int y) {
        return x % m < y % m;
    });

    int ans = 1e18;
    for (int i = 0; i < n; i++) {
        int start = i;
        int prev_val = a[start];
        modint now = start;
        int diff = 0;
        while (prev_val % m == a[now.val()] % m || (prev_val + 1) % m == a[now.val()] % m) {
            prev_val = a[now.val()];
            diff += a[now.val()];
            i++;
            now++;
            if (diff >= sum)
                break;
        }

        ans = min(ans, sum - diff);
        if (i >= n)
            break;
        i--;
    }
    cout << ans << endl;
}
