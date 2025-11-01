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
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if (c >= a) {
        if (d >= b) {
            cout << "No" << endl;
        } else
            cout << "Yes" << endl;
        return 0;
    }
    cout << "No" << endl;
}
