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
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    x.push_back(0);
    y.push_back(0);
    n++;
    ld ans = 0;
    int nx = 0, ny = 0;
    for (int i = 0; i < n; i++) {
        ans += hypot(nx - x[i], ny - y[i]);
        nx = x[i];
        ny = y[i];
    }
    cout << fixed << setprecision(10) << ans << endl;
}
