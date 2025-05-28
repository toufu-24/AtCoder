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
    int ans = 0;
    // for (int i = 0; i <= n; i++) {
    //     ans += (to_string(i).size() - 1) / 3;
    // }
    // cout << ans << endl;
    for (int digit = 4; digit <= to_string(n).size(); digit++) {
        int start = pow(10, digit - 1);
        int end = pow(10, digit) - 1;
        if (end > n) {
            end = n;
        }
        ans += (end - start + 1) * ((digit - 1) / 3);
    }
    cout << ans << endl;
}
