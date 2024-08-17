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
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        x[i]--;
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> idx(n);
    iota(all(idx), 0);
    for (int i = 0; i < k; i++) {
        vector<int> next_idx(n);
        for (int j = 0; j < n; j++) {
            next_idx[j] = idx[x[j]];
        }
        idx = next_idx;
    }

    for (int i = 0; i < n; i++) {
        cout << a[idx[i]] << " ";
    }
}
