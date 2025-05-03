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
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<vector<int>> a(m);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
            a[i][j]--;
        }
    }
    vector<vector<int>> zoo(n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < a[i].size(); j++) {
            zoo[a[i][j]].push_back(i);
        }
    }

    int ans = 1e18;
    for (int mask = 0; mask < (1L << (2 * n)); mask++) {
        vector<int> cnt(n, 0);
        for (int i = 0; i < 2 * n; i++) {
            if (mask & (1L << i)) {
                cnt[i % n]++;
            }
        }
        vector<int> animal_cnt(m, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < zoo[i].size(); j++) {
                animal_cnt[zoo[i][j]] += cnt[i];
            }
        }
        bool ok = true;
        for (int i = 0; i < m; i++) {
            if (animal_cnt[i] < 2) {
                ok = false;
                break;
            }
        }
        if (ok) {
            int tmp = 0;
            for (int i = 0; i < n; i++) {
                tmp += c[i] * cnt[i];
            }
            ans = min(ans, tmp);
        }
    }
    cout << ans << endl;
}
