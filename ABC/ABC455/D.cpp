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
    int n, q;
    cin >> n >> q;
    vector<int> c(q), p(q);
    for (int i = 0; i < q; i++) {
        cin >> c[i] >> p[i];
        c[i]--, p[i]--;
    }
    vector<int> up(n, -1), down(n, -1);
    for (int i = 0; i < q; i++) {
        int c_down = down[c[i]];
        if (c_down != -1) {
            up[c_down] = -1;
        }

        down[c[i]] = p[i];
        up[p[i]] = c[i];
    }

    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        if (down[i] == -1) { // 一番下なら
            int cnt = 0;
            int tmp = i;
            while (up[tmp] != -1) {
                tmp = up[tmp];
                cnt++;
            }
            ans[i] = cnt + 1;
        }
    }

    for (auto x : ans) {
        cout << x << " ";
    }
}
