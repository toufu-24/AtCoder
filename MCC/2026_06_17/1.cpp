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
    int idx = 0;
    while (true) {
        if (idx % 2 == 0) {
            c -= b;
            if (c <= 0) {
                cout << "Yes" << endl;
                return 0;
            }
        } else {
            a -= d;
            if (a <= 0) {
                cout << "No" << endl;
                return 0;
            }
        }
        idx++;
    }
}
