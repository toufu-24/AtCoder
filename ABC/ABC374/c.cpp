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
    vector<int> k(n);
    for (int i = 0; i < n; i++) {
        cin >> k[i];
    }

    int ans = LLONG_MAX;
    for (int mask = 0; mask < (1 << n); mask++) {
        // 0-> a, 1-> b
        int a = 0, b = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                a += k[i];
            } else {
                b += k[i];
            }
        }

        ans = min(ans, max(a, b));
    }
    cout << ans << endl;
}
