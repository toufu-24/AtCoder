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
    vector<int> gram(n, 0);
    for (int i = 0; i < n; i++) {
        gram[i] = a[i] * y;
    }

    int diff = y - x; // diffだけ a[i]回 引ける
    int ans = sum;
    int target = *min_element(all(gram));
    bool ok = true;
    for (int i = 0; i < n; i++) {
        if ((gram[i] - target) % diff == 0) {
            if ((gram[i] - target) / diff <= a[i]) {
                ans -= (gram[i] - target) / diff;
            } else {
                ok = false;
            }
        } else {
            ok = false;
        }
    }
    if (ok) {
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }
}
