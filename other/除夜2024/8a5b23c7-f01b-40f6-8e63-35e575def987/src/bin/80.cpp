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
    int _a, _b, _c;
    cin >> _a >> _b >> _c;
    modint::set_mod(24);
    modint a(_a), b(_b), c(_c);
    if ((a - c).val() < (b - c).val()) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
