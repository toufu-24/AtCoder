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
    int a, b, x;
    cin >> a >> b >> x;
    if (a == 0) {
        cout << b / x + 1 << endl;
        return 0;
    }
    cout << b / x - (a - 1) / x << endl;
}
