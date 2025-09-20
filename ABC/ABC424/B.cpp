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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<bool>> ac(n, vector<bool>(m, false));
    vector<int> a(k), b(k);

    vector<int> ans;
    for (int i = 0; i < k; i++) {
        cin >> a[i] >> b[i];
        a[i]--;
        b[i]--;
        ac[a[i]][b[i]] = true;
        for (int i = 0; i < n; i++) {
            int tmp = 0;
            for (int j = 0; j < m; j++) {
                if (ac[i][j]) {
                    tmp++;
                }
            }
            if (tmp == m) {
                if (find(ans.begin(), ans.end(), i) == ans.end()) {
                    ans.push_back(i);
                }
            }
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << " ";
    }
}
