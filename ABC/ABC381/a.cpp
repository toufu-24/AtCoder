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
    string s;
    cin >> s;
    if (n % 2 == 0) {
        cout << "No" << endl;
        return 0;
    }
    bool ok = true;
    for (int i = 0; i < (n + 1) / 2 - 1; i++) {
        if (s[i] != '1') {
            ok = false;
            break;
        }
    }
    if (s[(n + 1) / 2 - 1] != '/') {
        ok = false;
    }
    for (int i = (n + 1) / 2; i < n; i++) {
        if (s[i] != '2') {
            ok = false;
            break;
        }
    }

    cout << (ok ? "Yes" : "No") << endl;
}
