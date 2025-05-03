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
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    vector<string> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    int ans = 1e18;
    for (int i = 0; i < 4; i++) {
        // ずれカウント
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (s[j][k] != t[j][k]) {
                    cnt++;
                }
            }
        }
        ans = min(ans, cnt + i);

        // 90回転
        vector<string> tmp(n, string(n, ' '));
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                tmp[j][k] = s[n - k - 1][j];
            }
        }
        s = tmp;
    }
    cout << ans << endl;
}
