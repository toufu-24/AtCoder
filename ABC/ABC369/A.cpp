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
    int a, b;
    cin >> a >> b;
    int big = max(a, b);
    int small = min(a, b);
    int ans = 0;
    if (a == b) {
        cout << 1 << endl;
    } else if ((big - small) % 2 == 1) {
        cout << 2 << endl;
    } else {
        cout << 3 << endl;
    }
}
