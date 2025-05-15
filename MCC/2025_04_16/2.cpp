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
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    int ans = 0;
    modint::set_mod(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int d = 0; d < 8; d++) {
                string now = "";
                modint x = i, y = j;
                for (int k = 0; k < n; k++) {
                    now += a[x.val()][y.val()];
                    x += dx[d];
                    y += dy[d];
                }
                ans = max<long>(ans, stoll(now));
            }
        }
    }
    cout << ans << endl;
}
