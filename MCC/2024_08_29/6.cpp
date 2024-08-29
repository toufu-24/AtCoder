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
    vector<int> x45(n), y45(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        x45[i] = x[i] + y[i];
        y45[i] = x[i] - y[i];
    }
    int min_x45 = *min_element(all(x45));
    int max_x45 = *max_element(all(x45));
    int min_y45 = *min_element(all(y45));
    int max_y45 = *max_element(all(y45));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, max_x45 - x45[i]);
        ans = max(ans, x45[i] - min_x45);
        ans = max(ans, max_y45 - y45[i]);
        ans = max(ans, y45[i] - min_y45);
    }
    cout << ans << endl;
}
