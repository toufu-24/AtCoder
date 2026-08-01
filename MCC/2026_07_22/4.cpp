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
    int m;
    cin >> m;
    if (m < 100) {
        cout << "00" << endl;
    } else if (m <= 5000) {
        if (m < 1000) {
            cout << 0;
        }
        cout << m / 100 << endl;
    } else if (m <= 30000) {
        cout << m / 1000 + 50 << endl;
    } else if (m <= 70000) {
        cout << (m / 1000 - 30) / 5 + 80 << endl;
    } else {
        cout << "89" << endl;
    }
}
