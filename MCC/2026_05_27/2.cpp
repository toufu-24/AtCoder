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
    char s[3];
    for (int i = 0; i < 3; i++) {
        cin >> s[i];
    }
    char t[3];
    for (int i = 0; i < 3; i++) {
        cin >> t[i];
    }

    int same = 0;
    for (int i = 0; i < 3; i++) {
        same += (s[i] == t[i]);
    }

    if (same % 2 != 0) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
