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
    vector<int> t(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> v[i];
    }
    t.insert(t.begin(), 0);
    v.insert(v.begin(), 0);
    int ans = 0;
    for (int i = 1; i < v.size(); i++) {
        ans -= (t[i] - t[i - 1]);
        ans = max(ans, 0l);
        ans += v[i];
    }
    cout << ans << endl;
}
