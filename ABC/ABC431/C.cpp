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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> h(n), b(m);
    multiset<int> hst, bst;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        hst.insert(h[i]);
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        bst.insert(b[i]);
    }
    SORT(h);
    SORT(b);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        auto itr = bst.lower_bound(h[i]);
        if (itr == bst.end()) {
            break;
        }
        bst.erase(itr);
        ans++;
    }
    cout << ((ans >= k) ? "Yes" : "No") << endl;
}
