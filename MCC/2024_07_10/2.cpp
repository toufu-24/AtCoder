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
    int X;
    cin >> X;
    ld div = X / 10;
    int up = 1e18 + 1;
    int low = -1e18;
    while (up - low > 1) {
        int mid = (up + low) / 2;
        if (mid <= div) {
            low = mid;
        } else {
            up = mid;
        }
    }
    cout << low << endl;
}
