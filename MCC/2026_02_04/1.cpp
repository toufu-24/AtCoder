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
    if ((a + b) % 2 != 0) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    int mid = (a + b) / 2;
    cout << mid << endl;
}
