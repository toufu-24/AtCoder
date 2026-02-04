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
    vector<string> s(n), t(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i];
    }

    bool ok = true;
    for (int i = 0; i < n; i++) {
        bool s_ok = true;
        bool t_ok = true;
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            s_ok &= !(s[i] == s[j]);
            s_ok &= !(s[i] == t[j]);
            t_ok &= !(t[i] == t[j]);
            t_ok &= !(t[i] == s[j]);
        }
        ok &= (s_ok || t_ok);
    }
    cout << (ok ? "Yes" : "No") << endl;
}
