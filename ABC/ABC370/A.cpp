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
    int l, r;
    cin >> l >> r;
    if (l == 1) {
        if (r == 0) {
            cout << "Yes" << endl;
        } else {
            cout << "Invalid" << endl;
        }
    } else {
        if (r == 0) {
            cout << "Invalid" << endl;
            return 0;
        } else {
            cout << "No" << endl;
        }
    }
}
