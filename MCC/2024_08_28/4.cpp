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
    int n, m;
    cin >> n >> m;
    vector<int> seller(n), buyer(m);
    for (int i = 0; i < n; i++) {
        cin >> seller[i];
    }
    SORT(seller);
    for (int i = 0; i < m; i++) {
        cin >> buyer[i];
    }
    SORT(buyer);

    int ng = 0, ok = 1e18;
    while (abs(ok - ng > 1)) {
        int mid = (ok + ng) / 2;
        int sell_idx = upper_bound(all(seller), mid) - seller.begin();
        int buyer_idx = lower_bound(all(buyer), mid) - buyer.begin();
        if (sell_idx >= m - buyer_idx) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    cout << ok << endl;
}
