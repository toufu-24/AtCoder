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
    string s, t;
    cin >> s >> t;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != t[i]) {
            cout << "No" << endl;
            return 0;
        }
    }
    if (s.size() == t.size() - 1) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
