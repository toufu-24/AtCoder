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
    vector<int> a(9), b(8);
    for (int i = 0; i < 9; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < 8; i++) {
        cin >> b[i];
    }
    int as = reduce(all(a)), bs = reduce(all(b));
    cout << max(0L, as + 1 - bs) << endl;
}
