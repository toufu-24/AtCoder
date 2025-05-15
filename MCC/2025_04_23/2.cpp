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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        // b[i]--;
    }
    set<int> mochi;
    for (int i = 0; i < m; i++) {
        mochi.insert(b[i]);
    }

    int x;
    cin >> x;
    // x--;
    vector<int> dp(x + 1, 1e9);
    dp[0] = 0;
    for (int i = 0; i < x; i++) {
        if (dp[i] == 1e9) continue;
        if (mochi.contains(i)) continue;
        for (int j = 0; j < n; j++) {
            if (i + a[j] <= x) {
                dp[i + a[j]] = min(dp[i + a[j]], dp[i] + 1);
            }
        }
    }

    for (auto i : dp) {
        cerr << i << " ";
    }
    cerr << endl;
    if (dp[x] != 1e9) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
