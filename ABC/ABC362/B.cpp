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
    vector<complex<int>> v(3);
    for (int i = 0; i < 3; i++) {
        int x, y;
        cin >> x >> y;
        v[i] = {x, y};
    }

    auto dist2 = [](complex<int> a, complex<int> b) {
        return norm(a - b);
    };

    vector<int> d(3);
    d[0] = dist2(v[0], v[1]);
    d[1] = dist2(v[1], v[2]);
    d[2] = dist2(v[2], v[0]);

    SORT(d);

    if (d[0] + d[1] == d[2]) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
