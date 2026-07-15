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
    n--;
    vector<int> c(n), s(n), f(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> s[i] >> f[i];
    }

    for (int i = 0; i < n; i++) {
        int ans = 0;
        for (int j = i; j < n; j++) {
            // ans <= s[i] + x * f[i] で最小のx(>=0) を求める
            int left = -1, right = 1e9;
            while (abs(left - right) > 1) {
                int mid = (left + right) / 2;
                if (ans <= s[j] + mid * f[j]) {
                    right = mid;
                } else {
                    left = mid;
                }
            }

            ans = s[j] + right * f[j];
            ans += c[j];
        }
        cout << ans << endl;
    }
    cout << 0 << endl;
}
