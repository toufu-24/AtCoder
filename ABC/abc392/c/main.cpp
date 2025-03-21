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
    vector<int> p(n), q(n), revq(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        cin >> q[i];
        q[i]--;
        revq[q[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        ans[i] = q[p[revq[i]]];
        cout << ans[i] + 1 << " \n"[i == n - 1];
    }
}
