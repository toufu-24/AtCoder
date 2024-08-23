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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    map<int, vector<int>> idx;
    for (int i = 0; i < n; i++) {
        idx[a[i]].push_back(i);
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        // auto v = idx[x];
        int left = lower_bound(all(idx[x]), l) - idx[x].begin();
        int right = upper_bound(all(idx[x]), r) - idx[x].begin();
        cout << right - left << endl;
    }
}
