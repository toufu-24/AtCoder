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
    vector<vector<int>> revs(n);
    vector<vector<int>> s(m);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        s[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> s[i][j];
            s[i][j]--;
            revs[s[i][j]].push_back(i);
        }
    }
    vector<int> p(m);
    for (int i = 0; i < m; i++) {
        cin >> p[i];
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<bool> swi(n, false);
        vector<int> denkyu(m, 0);
        for (int i = 0; i < n; i++) {
            swi[i] = ((1 << i) & mask);
        }

        for (int i = 0; i < n; i++) {
            if (swi[i]) {
                for (int j = 0; j < revs[i].size(); j++) {
                    denkyu[revs[i][j]]++;
                }
            }
        }

        bool ok = true;
        for (int i = 0; i < m; i++) {
            ok &= (denkyu[i] % 2 == p[i]);
        }
        ans += ok;
    }
    cout << ans << endl;
}
