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
    int x, y, z;
    cin >> x >> y >> z;

    for (int i = 0; i < 1e7; i++) {
        if (x == y * z) {
            cout << "Yes" << endl;
            return 0;
        }
        x++;
        y++;
    }
    cout << "No" << endl;
}
