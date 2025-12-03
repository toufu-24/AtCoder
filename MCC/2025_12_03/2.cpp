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
    int t, a;
    cin >> t >> a;
    vector<int> h(n);
    vector<ld> deg(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        deg[i] = t - (ld)(0.006 * h[i]);
    }
    int ans = 0;
    ld diff = 1e18;
    for (int i = 0; i < n; i++) {
        if(diff > abs(a - deg[i])){
            ans = i + 1;
            diff = abs(a - deg[i]);
        }
    }
    cout << ans << endl;
}
