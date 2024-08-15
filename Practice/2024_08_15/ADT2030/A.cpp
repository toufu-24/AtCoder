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
    int M, D;
    cin >> M >> D;
    int y, m, d;
    cin >> y >> m >> d;
    d++;
    if (d > D) {
        d = 1;
        m++;
    }
    if (m > M) {
        m = 1;
        y++;
    }
    cout << y << " " << m << " " << d << endl;
}
