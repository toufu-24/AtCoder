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
    ld ans = 0;
    vector<map<int, int>> mps(n);
    // vector<int> a(k);
    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
            mps[i][a[i][j]]++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ld tmp = 0;
            if (mps[i].size() == 0 || mps[j].size() == 0) {
                continue;
            }
            for (auto [key, value] : mps[i]) {
                if (mps[j].contains(key)) {
                    tmp += value * mps[j][key] / (ld)(a[i].size() * a[j].size());
                }
            }
            ans = max(ans, tmp);
        }
    }
    cout << fixed << setprecision(20) << ans << endl;
}
