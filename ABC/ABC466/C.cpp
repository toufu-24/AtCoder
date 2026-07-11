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
    int right = 0;
    for (int i = 0; i < n - 1; i++) {
        ans += right - i;
        for (int j = right + 1; j < n; j++) {
            cout << "? " << i + 1 << " " << j + 1 << endl;
            string ret;
            cin >> ret;
            if (ret == "Yes") {
                ans++;
                right++;
            } else {
                break;
            }
        }
        right = max(right, i + 1);
    }
    cout << "! " << ans << endl;
}
