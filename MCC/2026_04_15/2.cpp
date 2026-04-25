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
    vector<vector<int>> idx(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        idx[a[i]].push_back(i);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int now_cnt = idx[i].size();
        // nowcnt C 2 * (n - now_cnt)
        int comb = now_cnt * (now_cnt - 1) / 2;
        ans += comb * (n - now_cnt);
    }
    cout << ans << endl;
}
