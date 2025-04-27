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
    string t, u;
    cin >> t >> u;
    for (int i = 0; i < t.size(); i++) {
        bool ok = true;
        for (int j = 0; j < u.size(); j++) {
            if (i + j >= t.size()) {
                ok = false;
                break;
            }
            if (t[i + j] != '?') {
                if (t[i + j] != u[j]) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}
