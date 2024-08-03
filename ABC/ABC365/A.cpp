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
    int y;
    cin >> y;
    bool ans = false;
    if (y % 4 != 0) {
        ans = true;
    } else if (y % 100 == 0) {
        if (y % 400 != 0) {
            ans = true;
        }
    }
    cout << (ans ? 365 : 366) << endl;
}
