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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        bool ans = false;
        SORT(a);
        int hi;
        if (a[1] % a[0] == 0) {
            hi = a[1] / a[0];
            bool tmp = true;
            for (int i = 2; i < n; i++) {
                if (a[i] % a[i - 1] == 0) {
                    hi = a[i] / a[i - 1];
                } else {
                    tmp = false;
                }
            }
            if (tmp) {
                ans = true;
            }
        }

        RSORT(a);
        int hi2;
        if (a[1] % a[0] == 0) {
            hi2 = a[1] / a[0];
            bool tmp = true;
            for (int i = 2; i < n; i++) {
                if (a[i] % a[i - 1] == 0) {
                    hi2 = a[i] / a[i - 1];
                } else {
                    tmp = false;
                }
            }
            if (tmp) {
                ans = true;
            }
        }
        if (ans) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
