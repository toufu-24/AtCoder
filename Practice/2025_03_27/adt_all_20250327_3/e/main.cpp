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

    int idx = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == tolower(t[idx])) {
            idx++;
            if (idx == 3) {
                break;
            }
        }
    }
    if (idx == 3) {
        cout << "Yes" << endl;
    } else if (idx == 2) {
        if (t.back() == 'X') {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    } else {
        cout << "No" << endl;
    }
}
