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
    double x;
    cin >> x;
    if (x < 37.5) {
        cout << 3 << endl;
    } else if (x < 38) {
        cout << 2 << endl;
    } else {
        cout << 1 << endl;
    }
}
