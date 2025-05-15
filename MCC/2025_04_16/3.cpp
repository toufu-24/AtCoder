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
    int n, q;
    cin >> n >> q;
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }
    SORT(r);
    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + r[i];
    }

    while (q--) {
        int x;
        cin >> x;
        int idx = upper_bound(all(sum), x) - sum.begin();
        idx--;
        cout << idx << endl;
    }
}
