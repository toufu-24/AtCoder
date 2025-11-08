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
    int x, n;
    cin >> x >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    int q;
    cin >> q;
    int ans = x;
    vector<bool> s(n, false);
    while (q--) {
        int p;
        cin >> p;
        p--;
        ans += w[p] * (s[p] ? -1 : 1);
        s[p] = !s[p];
        cout << ans << endl;
    }
}
