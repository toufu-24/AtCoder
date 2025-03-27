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
    int s, t, x;
    cin >> s >> t >> x;
    bool hannten = (t < s);
    if (hannten) {
        if (x >= s || x < t) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    } else {
        if (s <= x && x < t) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
