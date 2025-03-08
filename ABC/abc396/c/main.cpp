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
    vector<int> b(n), w(m);
    for (int i = 0; i < n; i++)
        cin >> b[i];
    for (int i = 0; i < m; i++)
        cin >> w[i];
    RSORT(b);
    RSORT(w);
    int ans = 0;
    int b_idx = 0;
    int w_idx = 0;
    while (b_idx < n) {
        if (b[b_idx] >= 0) {
            ans += b[b_idx];
            b_idx++;
        } else {
            break;
        }
    }
    while (w_idx < b_idx && w_idx < m) {
        if (w[w_idx] >= 0) {
            ans += w[w_idx];
            w_idx++;
        } else {
            break;
        }
    }

    // bは負だが，wは正の場合
    while (b_idx < n && w_idx < m) {
        if (b[b_idx] + w[w_idx] >= 0) {
            ans += b[b_idx] + w[w_idx];
            b_idx++;
            w_idx++;
        } else {
            break;
        }
    }

    cout << ans << endl;
}
